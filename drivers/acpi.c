/*
    MIT License
    (c) Antonio de Haro 2020

    See attached LICENSE file for more info

    drivers/acpi.c:
    Source file for the ACPI driver

    This has been mostly taken from a marvelous code example. 
    See: https://forum.osdev.org/viewtopic.php?t=16990

*/

#include <drivers/acpi.h>
#include <kernel/defs.h>

uint32_t *SMI_CMD;
uint8_t ACPI_ENABLE;
uint8_t ACPI_DISABLE;
uint32_t *PM1a_CNT;
uint32_t *PM1b_CNT;
uint16_t SLP_TYPa;
uint16_t SLP_TYPb;
uint16_t SLP_EN;
uint16_t SCI_EN;
uint8_t PM1_CNT_LEN;

struct rsdt {
    uint8_t Signature[8];
    uint8_t CheckSum;

    uint8_t OemID[6];
    uint8_t Revision;

    uint32_t *RsdtAddress;
};

struct facp {
    uint8_t Signature[4];
    uint32_t Length;

    uint8_t unneded1[40 - 8];

    uint32_t *DSDT;

    uint8_t unneded2[48 - 44];

    uint32_t *SMI_CMD;

    uint8_t ACPI_ENABLE;
    uint8_t ACPI_DISABLE;

    uint8_t unneded3[64 - 54];

    uint32_t *PM1a_CNT_BLK;
    uint32_t *PM1b_CNT_BLK;

    uint8_t unneded4[89 - 72];

    uint8_t PM1_CNT_LEN;
};

/* Check if the given address has a valid header */
uint32_t *acpi_check_rsd(uint32_t *ptr) {
    char *sig = "RSD PTR ";
    struct rsdt *rsdp = (struct rsdt *)ptr;

    uint8_t *bptr;
    uint8_t check = 0;
    uint32_t i;

    if (memcmp(sig, (char *)rsdp, 8) == 0) {
        bptr = (uint8_t *)ptr;
        for (i = 0; i < sizeof(struct rsdt); i++) {
            check += *bptr;
            bptr++;
        }

        // found valid rsdpd
        if (check == 0) {
            return (uint32_t *)rsdp->RsdtAddress;
        }
    }

    return NULL;
}

/* Finds the ACPI header and returns the address of the RSDT */
uint32_t *acpi_get_rsd() {
    uint32_t *addr;
    uint32_t *rsdp;

    // search below the 1mb mark for RSDP signature
    for (addr = (uint32_t *)0x000E0000; (int32_t)addr < 0x00100000; addr += 0x10 / sizeof(addr)) {
        rsdp = acpi_check_rsd(addr);

        if (rsdp != NULL) {
            return rsdp;
        }
    }

    // at address 0x40:0x0E is the RM segment of the ebda
    int32_t ebda = *((int16_t *)0x40E);  // get pointer
    ebda = ebda * 0x10 & 0x000FFFFF;     // transform segment into linear address

    // search Extended BIOS Data Area for the Root System Description Pointer signature
    for (addr = (uint32_t *)ebda; (int32_t)addr < ebda + 1024; addr += 0x10 / sizeof(addr)) {
        rsdp = acpi_check_rsd(addr);

        if (rsdp != NULL) {
            return rsdp;
        }
    }

    return NULL;
}

/* Checks for a given header and validates checksum */
int32_t acpi_check_header(uint32_t *ptr, char *sig) {
    if (memcmp((char *)ptr, (char *)sig, 4) == 0) {
        int8_t *checkPtr = (int8_t *)ptr;
        int32_t len = *(ptr + 1);
        int8_t check = 0;

        while (0 < len--) {
            check += *checkPtr;
            checkPtr++;
        }

        if (check == 0) {
            return 0;
        }
    }

    return -1;
}

/* Enables the ACPI */
int32_t acpi_enable() {
    // check if acpi is enabled
    if ((word_in((uint32_t)PM1a_CNT) & SCI_EN) == 0) {
        // check if acpi can be enabled
        if (SMI_CMD != 0 && ACPI_ENABLE != 0) {
            byte_out((uint32_t)SMI_CMD, ACPI_ENABLE);  // send acpi enable command
            // give 3 seconds time to enable acpi
            int32_t i;
            for (i = 0; i < 300; i++) {
                if ((word_in((uint32_t)PM1a_CNT) & SCI_EN) == 1) {
                    break;
                }

                reset_timer();  // This expects the timer to alrady be initialised
                while (get_tick() != 300) {
                    HLT();
                }
            }
            if (PM1b_CNT != 0)
                for (; i < 300; i++) {
                    if ((word_in((uint32_t)PM1b_CNT) & SCI_EN) == 1) {
                        break;
                    }

                    reset_timer();  // This expects the timer to alrady be initialised
                    while (get_tick() != 300) {
                        HLT();
                    }
                }
            if (i < 300) {
                return 0;  // Enabled ACPI
            } else {
                return -1;  // Couldn't enable ACPI
            }
        } else {
            return -1;  // No known way to enable the ACPI
        }
    } else {
        return 0;  // ACPI already enabled
    }
}

/* Initialises the ACPI */
int32_t acpi_init() {
    uint32_t *ptr = acpi_get_rsd();

    // check if address is correct  ( if acpi is available on this pc )
    if (ptr != NULL && acpi_check_header(ptr, "RSDT") == 0) {
        // the RSDT contains an unknown number of pointers to acpi tables
        int entrys = *(ptr + 1);
        entrys = (entrys - 36) / 4;
        ptr += 36 / 4;  // skip header information

        while (0 < entrys--) {
            // check if the desired table is reached
            if (acpi_check_header((uint32_t *)*ptr, "FACP") == 0) {
                entrys = -2;
                struct facp *facp = (struct facp *)*ptr;

                if (acpi_check_header((uint32_t *)facp->DSDT, "DSDT") == 0) {
                    // search the \_S5 package in the DSDT
                    char *S5Addr = (char *)facp->DSDT + 36;  // skip header
                    int dsdtLength = *(facp->DSDT + 1) - 36;

                    while (0 < dsdtLength--) {
                        if (memcmp(S5Addr, "_S5_", 4) == 0)
                            break;
                        S5Addr++;
                    }
                    // check if \_S5 was found
                    if (dsdtLength > 0) {
                        // check for valid AML structure
                        if ((*(S5Addr - 1) == 0x08 || (*(S5Addr - 2) == 0x08 && *(S5Addr - 1) == '\\')) && *(S5Addr + 4) == 0x12) {
                            S5Addr += 5;
                            S5Addr += ((*S5Addr & 0xC0) >> 6) + 2;  // calculate PkgLength size

                            if (*S5Addr == 0x0A) {
                                S5Addr++;  // skip byteprefix
                            }

                            SLP_TYPa = *(S5Addr) << 10;
                            S5Addr++;

                            if (*S5Addr == 0x0A) {
                                S5Addr++;  // skip byteprefix
                            }
                            
                            SLP_TYPb = *(S5Addr) << 10;

                            SMI_CMD = facp->SMI_CMD;

                            ACPI_ENABLE = facp->ACPI_ENABLE;
                            ACPI_DISABLE = facp->ACPI_DISABLE;

                            PM1a_CNT = facp->PM1a_CNT_BLK;
                            PM1b_CNT = facp->PM1b_CNT_BLK;

                            PM1_CNT_LEN = facp->PM1_CNT_LEN;

                            SLP_EN = 1 << 13;
                            SCI_EN = 1;

                            return 0;
                        }
                    }
                }
            }

            ptr++;
        }
    }

    return -1;  // Some error prevented the initialization
}

/* Instructs the power controller to invoke a system shutdown */
void acpi_poweroff() {
    // SCI_EN is set to 1 if acpi shutdown is possible
    if (SCI_EN == 0) {
        return;
    }

    acpi_enable();

    // send the shutdown command
    word_out((unsigned int)PM1a_CNT, SLP_TYPa | SLP_EN);

    if (PM1b_CNT != 0) {
        word_out((unsigned int)PM1b_CNT, SLP_TYPb | SLP_EN);
    }
}

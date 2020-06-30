; Loads a number dh of sectors (512 bytes) from drive
; dl into es:bx. Assumes that the disk to load has been 
; set by the BIOS into dl
disk_load:
    pusha ; Keep the registers intact
    push dx ; dx will be modified, so store it

    ; BIOS INTERRUPT PARAMETERS

    mov ah, 0x02 ; int 0x13 function mode 0x02 is READ
    mov al, dh   ; number of sectors to read
    mov cl, 0x02 ; First available sector (0x01 is the boot sector)
    mov ch, 0x00 ; Cylinder to load
    mov dh, 0x00 ; Head number
                 ; Keep in mind that dl is the drive to load from (set by BIOS)
                 ; Data will be written to es:bx

    int 0x13 ; BIOS interrupt
    jc .error ; if error (stored in the carry bit)

    pop dx ; Restore dx

    cmp al, dh ; BIOS also sets 'al' to the # of sectors read. Compare it.
    jne .error

    popa ; Restore registers
    ret ; Return from function

    .error:

    mov bx, .errormsg
    call print ; Print the error message

    mov dh, ah
    call hexprint

    hlt ; Halt the system

    .errormsg:
    db 'Error loading disk.', 0 ; Error message to print (NULL terminated)
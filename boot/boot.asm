;
; MIT License
; (c) Antonio de Haro, 2020
;
; See attached LICENSE file for more info.
;
; boot/boot.asm:
; Main bootloader file, defines the disk's bootsector

[org 0x7c00] ; Global offset
KERNEL_ENTRY equ 0x1000 ; This will store the location of the kernel entry point loaded from disk

mov [BOOT_DRIVE], dl ; Remember disk number set by BIOS
mov bp, 0x9000 ; Setup stack
mov sp, bp

mov bx, info0
call print ; Print wellcome message

mov bx, info1
call print ; Print info message

mov bx, KERNEL_ENTRY ; Read data will be stored here
mov dh, 16 ; Number of sectors to read
mov dl, [BOOT_DRIVE] ; Drive to read from
call disk_load

mov bx, info2
call print ; Print info message

call switch_pm ; Start protected mode

%include "print.asm"
%include "disk.asm"
%include "gdt.asm"

[bits 32]
begin_pm: ; This will be called once the switch has been made
    call KERNEL_ENTRY ; Give control to the kernel
    hlt ; Stay here when the kernel returns control to us

BOOT_DRIVE db 0 ; Store the boot drive number given by BIOS
info0 db "Starting 16-bit bootloader.", 0
info1 db "Loading kernel into memory.", 0
info2 db "Starting 32-bit kernel.", 0

times 510 - ($-$$) db 0 ; Filling out the rest of the sectory with 0
dw 0xaa55 ; Making this a boot sector
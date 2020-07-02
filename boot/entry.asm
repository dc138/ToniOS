;
; MIT License
; (c) Antonio de Haro, 2020
;
; See attached LICENSE file for more info.
;
; boot/entry.asm:
; Defines a bridge way to call C code from within assembly
;

[bits 32]
global _start ; So nasm doesn't complaint about a missing _strart

_start:
[extern entry] ; Define calling point as an external symbol for the linker
call entry

; If execution has reached this point, it means that the ACPI driver 
; failed to shut down the computer, so just disable interrupts and
; halt the system, a white 'E' on a red background will be printed
; on the bottom right of the screen to indicate the error

mov edx, 0xb8000 + 3998
mov al, 0x45
mov ah, 0xf4
mov [edx], ax

cli
hlt 

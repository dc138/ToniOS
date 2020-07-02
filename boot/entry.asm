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

mov edx, 0xb8000
mov al, 0x0
mov ah, 0xf0
mov [edx], ax

cli
hlt

;
; MIT License
; (c) Antonio de Haro, 2020
;
; See attached LICENSE file for more info.
;
; boot/entry.asm:
; Defines a bridge way to call C code from within assembly

[bits 32]
[extern entry] ; Define calling point as an external symbol for the linker

global _start ; So nasm doesn't complaint about a missing _strart
_start:
call entry
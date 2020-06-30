[bits 32]
[extern entry] ; Define calling point as an external symbol for the linker

global _start ; So nasm doesn't complaint about a missing _strart
_start:
call entry
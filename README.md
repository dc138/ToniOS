# ToniOS

A very simple 32-bit i386 based OS with a simple monolithic kernel. This OS
is based in, among others, cfenollosa's wonderful os-tutorial 
*(https://github.com/cfenollosa/os-tutorial)*.

## About

This is a very simple OS that I have been developing to learn more about
assembly and low level C. It is has been designed from scratch to work 
on an i386 system, taking full advantage of the extended 32-bit registers. 

This project has been well commented, both on the assembler as well as the
C code, and, as such, is meant for anyone who wants to learn about or learn 
how to make something similar. It also includes a debug make target to help 
debug the kernel.

This OS has been compiled with a custom compiled binutils, gcc and gdb to
target the i386 arhitecture. The C code has been compiled with the -ffreestanding
compiler flag to make it embedeable and, as such, this project has no
dependencies.

It follows a monolithic kernel design written in C. As well as a 16-bit 
bootloader capable of booting with a BIOS. 

A UEFI booting system, as well as other procesor architectures/platforms are 
and will not be supported.

## Current state

The current kernel includes a input() function to make ir process a command, as 
well as a ACPI driver and IRS setup with custom IRQs to process a timer and keyboard
keys with a standard US keymap.

## Licensing

This project is released under the MIT license.

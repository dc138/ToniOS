#
# MIT License
# (c) Antonio de Haro, 2020
#
# See attached LICENSE file for more info.
#

#
# Run 'make run' to compile and run, configure with
# your own cross compiling compiler
#

# Compiler version selection

QEMU := /usr/bin/qemu-system-i386

CC := /usr/local/i386elfgcc/bin/i386-elf-gcc
LD := /usr/local/i386elfgcc/bin/i386-elf-ld
GDB := /usr/local/i386elfgcc/bin/i386-elf-gdb
NASM := /usr/bin/nasm

CFLAGS := -g -ffreestanding -I. -std=c99 -O2


# Recursively finding project source files

CSOURCES := $(shell find . -type f -name *.c)
CHEADERS := $(shell find . -type f -name *.h)


# Target file to build

BUILD := build
BUILDDIRS := $(BUILD)/boot $(BUILD)/cpu $(BUILD)/drivers $(BUILD)/kernel $(BUILD)/libc
TARGET := $(BUILD)/ToniOS.img


# Different object files rules depending on the source file type (C or assembly)

COBJ := $(patsubst ./%,$(BUILD)/%,$(CSOURCES:.c=.o)) # Fixing up the directory to include build/ and remove the .
ASMOBJ := $(BUILD)/cpu/itr.o


# General rules

all: $(TARGET)

run: $(TARGET)
	$(QEMU) -drive format=raw,file=$(TARGET),index=0,if=floppy -boot b

debug: $(TARGET) $(BUILD)/kernel/kernel.elf
	$(QEMU) -s -S -drive format=raw,file=$(TARGET),index=0,if=floppy -boot b &
	$(GDB) -ex "symbol-file $(BUILD)/kernel/kernel.elf" -ex "set arch i386" -ex "target remote localhost:1234" -ex "b kernel.c:entry" -ex "c"

clean:
	rm -rfv $(BUILD)/

.PHONY: all run debug clean


# File specific rules

# Rule to create the final OS image by contatenation, not that the 
# build directoryies must be created first
$(TARGET): $(BUILD) $(BUILDDIRS) $(BUILD)/boot/boot.bin $(BUILD)/kernel/kernel.bin
	cat $(BUILD)/boot/boot.bin $(BUILD)/kernel/kernel.bin > $(TARGET)

# Rule to generate build directory
$(BUILD):
	mkdir $@

# Rule to generate build directorys
$(BUILDDIRS):
	mkdir $@

# Compiling the bootloader from its only source
$(BUILD)/boot/boot.bin: boot/boot.asm
	$(NASM) $< -f bin -o $@ -i boot/

# The kernel requires all of the C generated object files as well as the special
# entry.o that allows us to call the previously loaded C written Kernel from assembly
$(BUILD)/kernel/kernel.bin: $(BUILD)/boot/entry.o $(COBJ) $(ASMOBJ)
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# Special rule to generate the kernel's symboll file to debbug it in case it is neccesary
$(BUILD)/kernel/kernel.elf: $(BUILD)/boot/entry.o $(COBJ) $(ASMOBJ)
	$(LD) -o $@ -Ttext 0x1000 $^

# Rule to compile this special kernel entry object file
$(BUILD)/boot/entry.o: boot/entry.asm
	$(NASM) $< -f elf -o $@

# There is still room for improvement here since we only need to recompile if 
# the .c file required for this .o has changed, but I havent been able to do so.
# Notice how we also include the header files as depencencies, as a recompilation
# is also needed if we change one them
$(COBJ): $(CSOURCES) $(CHEADERS) 
	$(CC) $(CFLAGS) -c $(patsubst %.o,%.c,$(patsubst $(BUILD)/%,%,$@)) -o $@

# Rule ro compile some object files that do not participate in the booting proces
# nor Kernel loading rutines but are still written in asssembly instead of C for
# ease of coding
$(ASMOBJ): $(patsubst $(BUILD)/%.o,%.asm,$(ASMOBJ))
	$(NASM) $< -f elf -o $@

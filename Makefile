# Compiler version selection

QEMU := /usr/bin/qemu-system-i386

CC := /usr/local/i386elfgcc/bin/i386-elf-gcc
LD := /usr/local/i386elfgcc/bin/i386-elf-ld
GDB := /usr/local/i386elfgcc/bin/i386-elf-gdb
NASM := /usr/bin/nasm

CFLAGS := -g -ffreestanding -I. -std=c99


# Recursively finding project source files

CSOURCES := $(shell find . -type f -name *.c)
CHEADERS := $(shell find . -type f -name *.h)
OBJ := $(patsubst ./%,build/%,$(CSOURCES:.c=.o)) # Fixing up the directory to include build/ and remove the .


# Target file to build

BUILD := build
TARGET := $(BUILD)/ToniOS.img


# General rules

all: $(TARGET)

run: $(TARGET)
	$(QEMU) -drive format=raw,file=$(TARGET),index=0,if=floppy -boot b

debug: $(TARGET) $(BUILD)/kernel/kernel.elf
	$(QEMU) -s -S -drive format=raw,file=$(TARGET),index=0,if=floppy -boot b &
	$(GDB) -ex "symbol-file $(BUILD)/kernel/kernel.elf" -ex "set arch i386" -ex "target remote localhost:1234" -ex "b kernel.c:entry" -ex "c"

clean:
	find build/ -type f -name '*' -delete

.PHONY: all run debug clean


# File specific rules

# Rule to create the final OS image by contatenation
$(TARGET): $(BUILD)/boot/boot.bin $(BUILD)/kernel/kernel.bin
	cat $^ > $(TARGET)

# Compiling the bootloader from its only source
$(BUILD)/boot/boot.bin: boot/boot.asm
	$(NASM) $< -f bin -o $@ -i boot/

# The kernel requires all of the C generated object files as well as the special
# entry.o that allows us to call the previously loaded C written Kernel from assembly
$(BUILD)/kernel/kernel.bin: $(BUILD)/boot/entry.o $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# Special rule to generate the kernel's symboll file to debbug it in case it is neccesary
$(BUILD)/kernel/kernel.elf: $(BUILD)/boot/entry.o $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^

# Rule to compile this special kernel entry object file
$(BUILD)/boot/entry.o: boot/entry.asm
	$(NASM) $< -f elf -o $@

# There is still room for improvement here since we only need to recompile if 
# the .c file required for this .o has changed, but I havent been able to do so.
# Notice how we also include the header files as depencencies, as a recompilation
# is also needed if we change one them
$(OBJ): $(CSOURCES) $(CHEADERS) 
	$(CC) $(CFLAGS) -c $(patsubst %.o,%.c,$(patsubst build/%,%,$@)) -o $@


/* 
    MIT License
    (c) Antonio de Haro 2020

    See attached LICENSE file for more info

    drivers/keyboard.c:
    TODO

*/

#include <cpu/isr.h>
#include <cpu/ports.h>
#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <kernel/kernel.h>
#include <libc/mem.h>
#include <libc/str.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define SC_MAX 57

static char key_buffer[256];

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs) {
    UNUSED(regs);
    uint8_t scancode = byte_in(0x60);

    if (scancode > SC_MAX) return;  // Unsupported key

    if (scancode == BACKSPACE) {
        if (strlen(key_buffer) == 0) return;

        backspace(key_buffer);
        print_backspace();
    } else if (scancode == ENTER) {
        print("\n");
        input(key_buffer);  // Kernel-controlled function

        memset(key_buffer, '\0', strlen(key_buffer));
    } else {
        char letter = sc_ascii[(int)scancode];
        char str[2] = {letter, '\0'};

        append(key_buffer, letter);
        print(str);
    }
}

void init_keyboard() {
    memset(key_buffer, '\0', 256);
    register_interrupt_handler(IRQ1, keyboard_callback);
}

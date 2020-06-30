;
; MIT License
; (c) Antonio de Haro, 2020
;
; See attached LICENSE file for more info.
;
; boot/print.asm;
; Bootloader utility file

; Takes a null terminated string pointer from bx as 
; argument and prints it with the BIOS
print:
	pusha ; Keep the registers intact
    mov ah, 0x0e ; TTY mode

    .loop:

    mov al, [bx] ; Load current charracter
    cmp al, 0 ; Check for end of string
    je .endloop ; Finish if null character

    int 0x10 ; Print the current character
    add bx, 1 ; Increment the current char pointer
    jmp .loop ; Restart the loop

    .endloop:

    mov al, 0x0a ; New line character
    int 0x10 ; Print it

    mov al, 0x0d ; Carriage return cahracter
    int 0x10 ; Print it

    popa ; Pop the registers back
    ret ; Return to the code we were executing

; Takes a hex value from dx as an argument and prints
; it's string representation wit the format 0x0000
hexprint:
    pusha

    mov cx, 0 ; Index variable

    .loop:

    cmp cx, 4 ; Loop 4 times
    je .endloop
    
    ; 1. convert last char of 'dx' to ascii
    mov ax, dx ; we will use 'ax' as our working register
    and ax, 0x000f ; 0x1234 -> 0x0004 by masking first three to zeros
    add al, 0x30 ; add 0x30 to N to convert it to ASCII "N"
    cmp al, 0x39 ; if > 9, add extra 8 to represent 'A' to 'F'
    jle .next
    add al, 7 ; 'A' is ASCII 65 instead of 58, so 65-58=7

    .next:
    ; 2. get the correct position of the string to place our ASCII char
    ; bx <- base address + string length - index of char
    mov bx, .out + 5 ; base + length
    sub bx, cx  ; our index variable
    mov [bx], al ; copy the ASCII char on 'al' to the position pointed by 'bx'
    ror dx, 4 ; 0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234

    ; increment index and loop
    add cx, 1
    jmp .loop

    .endloop:
    ; prepare the parameter and call the function
    ; remember that print receives parameters in 'bx'
    mov bx, .out
    call print

    popa
    ret

    .out:  
    db '0x0000',0 ; Reserve memory for our new string
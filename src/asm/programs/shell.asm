BITS 16

extern kernel_clear
extern kernel_backspace
extern kernel_print
extern kernel_print_ln
extern kernel_print_char
extern kernel_halt
extern video_set_pixel
extern parse_input

global shell_main

shell_main:
.start:
    mov si, prompt ; print prompt character
    call kernel_print

    mov si, buffer ; setup character buffer and pointer
    mov di, buffer

    mov al, 0
    mov di, buffer
    mov cx, 255
    rep stosb

    mov si, buffer
    mov di, buffer

.loop:
    mov ah, 0h ; Reads key, stores output in AH, AL
    int 16h

    cmp al, 08h ; backspace key
    je .backspace

    cmp al, 0Dh ; enter key
    je .done

    cmp di, buffer + 256
    je .loop ; if typing past buffer limit, just idk loop back

    mov [di], al ; add character to buffer, and print character
    inc di
    call kernel_print_char
    jmp .loop

.backspace:
    mov al, 0
    mov [di], al
    cmp si, di
    je .loop
    dec di
    call kernel_backspace
    jmp .loop

.done:
    mov si, empty
    call kernel_print_ln

    mov si, buffer
    call parse_input

    mov si, empty
    call kernel_print_ln

    jmp .start

    call kernel_halt

empty: db "", 0
prompt: db "> ", 0
buffer: times 256 db 0
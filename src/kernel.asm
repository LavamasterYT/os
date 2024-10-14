BITS 16

extern shell_main

kernel_entry:
    call shell_main
    hlt

page db 0

; Clears the screen
global kernel_clear
kernel_clear: 
    mov ah, 06h ; Set interrupt to scroll up
    mov al, 0h ; lines to scroll (0 for clear)
    mov bh, 07h ; set black background and white foreground
    mov ch, 0h ; starting row number
    mov cl, 0h ; starting column number
    mov dh, 18h ; ending row number, 24
    mov dl, 4Fh ; ending column number, 79
    int 10h

    mov ah, 0Fh ; get current video mode, used for retrieving page
    int 10h
    mov [page], bh

    mov ah, 02h ; set cursor position, page value already set by above call
    xor dx, dx ; set cursor postition to 0
    int 10h

    ret

; Prints a string
; args:
; si - pointer to null terminated string
global kernel_print
kernel_print:
    mov ah, 0Eh
    mov bh, [page]
.kernel_print_loop:
    lodsb
    test al, al
    jz .kernel_print_done
    int 10h
    jmp .kernel_print_loop
.kernel_print_done:
    ret

; Prints a string along with a new line
; args:
; si - pointer to null terminated string
global kernel_print_ln
kernel_print_ln:
    call kernel_print
    mov al, 0Ah
    int 10h
    mov al, 0Dh
    int 10h
    ret

; prints a character
; args:
; al - ascii character
global kernel_print_char
kernel_print_char:
    mov ah, 0Eh
    mov bh, [page]
    int 10h
    ret

; goes back one space, and remove character on that space
global kernel_backspace
kernel_backspace:
    mov ah, 03h
    mov bh, [page]
    int 10h

    dec dl
    mov ah, 02h
    int 10h

    mov ah, 0Ah
    mov al, ' '
    mov cx, 1
    int 10h
    
    ret

; halts, inifinite loop
global kernel_halt
kernel_halt: hlt
    jmp kernel_halt
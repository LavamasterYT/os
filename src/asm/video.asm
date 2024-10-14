BITS 16

; 0xDF

; Draws a pixel at a x,y
; args:
; dl - x
; dh - y
; bl - color
; color - lower 4 background, upper 4 foreground
; ex. if 0 is black and F is white, 0F for black background, white foreground
; 02h - set cursor position, bh page number, dh row, dl column
; 08h - read at cursor, bh page number, return ah color, al character
; 09h - write charcater, al character, bh page num, bl col, cx 1
; div - given x / y = z, x is ax, y is operand, al stores result, ah stores remainder
; bitwise, first operand stores result
; what should this do?
; first determine the x and y position for the cursor and set that position
; read color data
; check if modifying top or bottom pixel, then edit color attributes
; draw character
global video_set_pixel
video_set_pixel:
    push bx ; store color for later use

    ; divide to determine correct cursor position
    mov ax, dx
    mov al, ah
    xor ah, ah
    mov bl, 2
    div bl ; quotient in al, remainder is in ah

    push ax

    mov dh, al
    mov bh, 0
    mov ah, 02h
    int 10h ; set the cursor position

    mov ah, 08h
    int 10h ; get color data on current cursor

    cmp al, 0xDF ; if no pixel written, we can assume its black 
    je .has_pixel
    mov ah, 0
.has_pixel:
    mov ch, ah

    pop ax
    pop bx

    ; if remainder is zero, edit foreground else edit background
    test ah, ah
    jne .change_background
    and bl, 0x0F
    and ch, 0xF0
    or bl, ch
    jmp .draw
.change_background:
    and bl, 0xF0
    and ch, 0x0F
    or bl, ch
.draw:
    mov ah, 09h
    mov al, 0xDF
    mov bh, 0
    mov cx, 1
    int 10h
    ret


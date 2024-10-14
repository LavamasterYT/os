BITS 16

extern video_set_pixel
extern kernel_clear

global game_main
game_main:
    ; Set cursor to none
    mov ah, 01
    mov cx, 2607h
    int 10h

    call kernel_clear

    ; Main game loop
    mov [player], word 0
.game_loop:
    call kernel_clear

    ; Draw player to screen
    mov dx, [player]
    mov bl, 0xAA
    call video_set_pixel

    mov ah, 0h ; Reads key, stores output in AH, AL
    int 16h

; Update player positions
    mov dx, [player]
    cmp ah, 0x48 ; up arrow
    je .up
    cmp ah, 0x50 ; down arrow
    je .down
    cmp ah, 0x4B ; left arrow
    je .left
    cmp ah, 0x4D ; right arrow
    je .right
    cmp al, 0x1B
    je .done
    jmp .cont

.up:
    test dh, dh
    jz .set_49
    dec dh
    jmp .cont

.down:
    cmp dh, 49
    je .set_y_0
    inc dh
    jmp .cont

.left:
    test dl, dl
    jz .set_79
    dec dl
    jmp .cont

.right:
    cmp dl, 79
    je .set_x_0
    inc dl
    jmp .cont

.set_49:
    mov dh, 49
    jmp .cont

.set_y_0:
    mov dh, 0
    jmp .cont

.set_79:
    mov dl, 79
    jmp .cont

.set_x_0:
    mov dl, 0
    jmp .cont

.cont:
    mov [player], dx
    jmp .game_loop

.done:
    ; Reset dx
    mov dx, 0

    call kernel_clear

    ; Set cursor back to underline
    mov ah, 01
    mov cx, 0607h
    int 10h
    ret

player: dw 0
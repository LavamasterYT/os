BITS 16

cmd_buffer: times 256 db 0

str_unknown: db "Unknown command: ", 0
str_cmd_clear: db "clear", 0
str_cmd_echo: db "echo", 0
str_cmd_halt: db "halt", 0
str_cmd_game: db "game", 0
str_cmd_protected: db "32", 0

extern kernel_clear
extern kernel_halt
extern game_main
extern kernel_print
extern enter_protected_mode

global parse_input
parse_input:
    push si

    mov al, 0
    mov di, cmd_buffer
    mov cx, 255
    rep stosb

    pop si

    mov di, cmd_buffer

.loop1:
    lodsb
    test al, al
    jz .compare
    cmp al, ' '
    je .compare
    mov [di], al
    inc di
    jmp .loop1

.compare:
    push si

    mov di, cmd_buffer
    mov si, str_cmd_clear
    call compare_string
    test al, al ; if return value is 0, it means strings matched
    jz .clear_cmd

    mov di, cmd_buffer
    mov si, str_cmd_game
    call compare_string
    test al, al
    jz .game_cmd

    mov di, cmd_buffer
    mov si, str_cmd_echo
    call compare_string
    test al, al
    jz .echo_cmd

    mov di, cmd_buffer
    mov si, str_cmd_halt
    call compare_string
    test al, al
    jz .halt_cmd

    mov di, cmd_buffer
    mov si, str_cmd_protected
    call compare_string
    test al, al
    jz .protected_cmd

    jmp .unknown_cmd

.clear_cmd:
    pop si
    call kernel_clear
    jmp .done

.game_cmd:
    pop si
    call game_main
    jmp .done

.echo_cmd:
    pop si
    call kernel_print
    jmp .done

.protected_cmd:
    pop si
    call enter_protected_mode
    jmp .done

.halt_cmd:
    pop si
    call kernel_halt
    jmp .done

.unknown_cmd:
    pop si

    mov si, str_unknown
    call kernel_print

    mov si, cmd_buffer
    call kernel_print

.done:
    ret

compare_string:
    ; si contains command
    ; di contains input

    xor bx, bx
.cmp_loop:
    mov al, [di + bx]
    cmp al, [si + bx]
    jne .ne
    inc bx
    test al, al
    jnz .cmp_loop
    mov al, 0
    ret

.ne:
    mov al, 1
    ret
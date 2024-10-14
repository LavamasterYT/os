BITS 16

extern kernel_print_ln
extern c_main

global enter_protected_mode
enter_protected_mode:
    mov si, msg
    call kernel_print_ln

    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp 0x08:protected_main

BITS 32

protected_main:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    pushad
    mov edi, 0x112345
    mov esi, 0x012345
    mov [esi], esi
    mov [edi], edi
    cmpsd
    popad
    jne .a20_off
    jmp .halt_loop

.a20_off:
    call enable_a20

.halt_loop:
    call c_main
    jmp $
    hlt

enable_a20:
    cli 

    call a20_wait
    mov al, 0xAD
    out 0x64, al

    call a20_wait
    mov al, 0xD0
    out 0x64, al

    call a20_wait2
    in al, 0x60
    push eax

    call a20_wait
    mov al, 0xD1
    out 0x64, al

    call a20_wait
    pop eax
    or al, 2
    out 0x60, al

    call a20_wait
    mov al, 0xAE
    out 0x64, al

    call a20_wait
    ret

a20_wait:
    in al, 0x64
    test al, 2
    jnz a20_wait
    ret

a20_wait2:
    in al, 0x64
    test al, 1
    jz a20_wait2
    ret

gdt_start:
    dw 0x0000              ; Null descriptor
    dw 0x0000
    dw 0x0000
    dw 0x0000

gdt_code:
    dw 0xFFFF              ; Code segment descriptor
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

gdt_data:
    dw 0xFFFF              ; Data segment descriptor
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

msg: db "Entering protected mode. . .", 0
pmsg: db "In protected mode!", 0
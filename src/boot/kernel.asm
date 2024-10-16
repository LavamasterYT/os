BITS 16

section .text.startup

extern kernel_main
global _start

_start:
    mov si, loaded_str
    call print_str

    mov si, protected_env
    call print_str

    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp 0x08:protected_main

.halt:
    hlt
    jmp .halt

print_str:
    mov ah, 0Eh
.print_loop:
    lodsb
    test al, al
    jz .print_done
    int 10h
    jmp .print_loop
.print_done:
    ret

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
    jmp .cont
.a20_off:
    call enable_a20
.cont:
    call kernel_main
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

loaded_str: db "Loaded kernel!", 0x0A, 0x0D, 0
protected_env: db "Loading protected environment. . .", 0x0A, 0x0D, 0
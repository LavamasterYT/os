BITS 16

section .text.startup

extern main
extern tty_init
extern init_memory

global _start

_start:
    mov si, loaded_str
    call print_str

    mov si, getting_mem
    call print_str

    mov ax, 0 ; Load memory map structure array to es:di
    mov es, ax
    lea di, [nmap]

    xor ebx, ebx ; Clear ebx bit
    mov ecx, 0 ; Counter for 256 entries on memory map

.mem_loop:
    push ecx ; Save counter value

    mov eax, 0xE820 ; Function code for querying memory map
    mov edx, 0x534D4150 ; 'SMAP'
    mov ecx, 24 ; Size of memory map structure
    int 15h
    jc .err ; Error querying memory map

    add di, 24 ; Increase es:di by 24, next entry
    pop ecx ; Retrieve counter value
    inc ecx ; Increase it
    cmp ecx, 256 ; Is it max entries?
    je .err ; It is, so we are done
    test ebx, ebx ; Did the BIOS function say we are done?
    jz .err ; Then we are
    jmp .mem_loop

.err:
    dec ecx
    mov [nmap_len], ecx ; Store length

    mov si, protected_env
    call print_str

    ; Setup protected mode to run 32 bit
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
    ; Setting up segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Test for a20 line
    pushad
    mov edi, 0x112345
    mov esi, 0x012345
    mov [esi], esi
    mov [edi], edi
    cmpsd
    popad

    ; Enable a20 if necessary
    je .a20_on
    call enable_a20
.a20_on:
    ; Call kernel_main
    mov ecx, [nmap_len]
    push ecx
    push nmap
    call init_memory
    call tty_init

    call main
    
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
getting_mem: db "Getting memory. . .", 0x0A, 0x0D, 0
got_mem: db "Got memory. . .", 0x0A, 0x0D, 0
err_mem: db "Error getting memory", 0x0A, 0x0D, 0
protected_env: db "Loading protected environment. . .", 0x0A, 0x0D, 0

nmap_len: dq 0
nmap: times 6144 db 0
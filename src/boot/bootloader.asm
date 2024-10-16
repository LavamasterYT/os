BITS 16
ORG 0x7C00

bootloader_entry:
    ; Setup segment registers and stack
    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov sp, bootloader_entry

    ; Disable interrupts and clear direction flag
    cld
    cli

    mov [disk], dl ; Store disk

    mov si, loading_str
    call print_str


    mov ah, 02h ; Read sectors interrupt
    mov al, 8 ; Sectors to read
    mov dl, [disk] ; Disk to read
    mov ch, 0 ; Cylinder number
    mov cl, 2 ; Starting sector, 2 because we are skipping bootloader
    mov dh, 0 ;  Head number
    mov bx, 1000h ; Address to load to
    int 13h

    jmp 100h:0000 ; Jump to kernel

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

disk: db 0
loading_str: db "Loading kernel...", 0x0A, 0x0D, 0

times 510 - ($ - $$) db 0
dw 0xAA55
BITS 16
ORG 0x7C00

bl_entry:
    ; setup segment registers, stack, etc
    xor ax, ax
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov sp, bl_entry

    cld
    cli
    
    mov [disk], dl

    mov si, loading_str
    call bl_print_str

    ; Read disk to 0x1000
    mov ah, 02h ; Read sectors
    mov al, 8 ; Number of sectors to read
    mov dl, [disk] ; Disk number
    mov ch, 0 ; Cylinder number
    mov cl, 2 ; Starting sector number, in theory the bootloader is sector 1
    mov dh, 0 ; Head number
    mov bx, 1000h ; Address to load to
    int 13h

    mov si, done_str
    call bl_print_str

    jmp 100h:0000 ; Just to 0x1000

bl_print_str:
    mov ah, 0Eh
.print_loop:
    lodsb
    cmp al, 0
    je .print_done
    int 10h
    jmp .print_loop
.print_done:
    ret

halt: hlt
    jmp halt

disk db 0x80
done_str db "Loaded kernel!", 0Ah, 0Dh, 0
loading_str db "Loading from disk. . .", 0Ah, 0Dh, 0

times 510-($-$$) db 0
dw 0xAA55
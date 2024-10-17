BITS 16
ORG 0x7C00

boot:
    jmp bootloader_entry
    times 3-($-$$) db 0x90
    db "mkfs.fat"
    dw 512
    db 1
    dw 1
    db 2
    dw 224
    dw 2880
    db 0xf0
    dw 9
    dw 18
    dw 2
    dd 0
    dd 0
    db 0
    db 0
    db 0x29
    dd 0x2d7e5a1a
    db "NO NAME    "
    db "FAT12   "

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
    mov al, 32 ; Sectors to read
    mov dl, [disk] ; Disk to read
    mov ch, 0 ; Cylinder number
    mov cl, 2 ; Starting sector, 2 because we are skipping bootloader
    mov dh, 0 ;  Head number
    mov bx, 1000h ; Address to load to
    int 13h

    jc .bootloader_error
    
    jmp 1000h ; Jump to kernel

.bootloader_error:
    mov si, err_str
    call print_str
.halt_loop:
    hlt
    jmp .halt_loop

print_str:
    mov ah, 0Eh ; Teletype char function code
.print_loop:
    lodsb ; Load byte from si to al and inc al
    test al, al ; Is al 0 aka null character
    jz .print_done ; End of string
    int 10h ; Print character in al
    jmp .print_loop
.print_done:
    ret

disk: db 0
loading_str: db "Loading kernel...", 0x0A, 0x0D, 0
err_str: db "Error loading kernel. Aborting!", 0x0A, 0x0D, 0

times 510 - ($ - $$) db 0
dw 0xAA55
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <kernel/memory.h>
#include <kernel/vga.h>

void kernel_main(nmap *memory, int len)
{
    int ret = init_memory(memory, len);

    if (ret)
        vga_write_str_at("Unable to setup memory manager!", 0, 0, VGA_BLACK, VGA_WHITE);

    vga_enable_cursor();
    vga_set_cursor_position(0, 0);
    vga_clear(VGA_BLACK, VGA_WHITE);

    char buffer[16];
    int num = 0;

    for (int i = 0; i < len; i++)
        printf("Base Address: %#.8llx | Length: %#.8llx\n", memory[i].base_addr, memory[i].len);
}
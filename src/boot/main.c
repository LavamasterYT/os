#include <string.h>
#include <stdlib.h>

#include <kernel/memory.h>
#include <kernel/vga.h>

void kernel_main(nmap* memory)
{
    char str[] = "This is a test.";
    char buffer[16];

    vga_disable_cursor();
    vga_enable_cursor();
    vga_clear();
    
    vga_write_str_at(str, 0, 0);
    vga_write_str_at(ultoa(memory->len, buffer, 16), 0, 1);

    while (1)
    {

    }
}
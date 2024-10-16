#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <kernel/vga.h>

void kernel_main()
{
    char input[] = "This is a test string.";

    vga_disable_cursor();
    vga_enable_cursor();
    vga_clear();
    
    vga_write_str_at((char*)memchr(input, '4', strlen(input)), 0, 0);

    while (1)
    {

    }
}
#include <stdint.h>
#include <stddef.h>

#include "kernel/vga.h"

void c_main()
{
    vga_disable_cursor();
    vga_clear();
    vga_write_str_at("In protected mode!", 0, 0);

    while (1)
    {

    }
}
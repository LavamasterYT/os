#include <string.h>
#include <stdlib.h>

#include <kernel/memory.h>
#include <kernel/vga.h>

void kernel_main(nmap *memory, int len)
{
    char addr_base[16];
    char addr_len[16];
    char addr_acpi[16];

    vga_disable_cursor();
    vga_enable_cursor();
    vga_clear();

    for (int i = 0; i < len; i++)
    {
        ultoa(memory[i].base_addr, addr_base, 16);
        ultoa(memory[i].len, addr_len, 16);
        itoa(memory[i].acpi, addr_acpi, 16);

        int c = 0;

        c = vga_write_str_at("base: 0x", 0, i);
        c = vga_write_str_at(addr_base, c, i);

        c = vga_write_str_at(" | len: 0x", c, i);
        c = vga_write_str_at(addr_len, c, i);

        c = vga_write_str_at(" | type: ", c, i);

        if (memory[i].type == 1)
            c = vga_write_str_at("free | ", c, i);
        else if (memory[i].type == 2)
            c = vga_write_str_at("reserved | ", c, i);
        else
            c = vga_write_str_at("reserved | ", c, i);

        c = vga_write_str_at("acpi: ", c, i);
        vga_write_str_at(addr_acpi, c, i);
    }

    while (1)
    {
    }
}
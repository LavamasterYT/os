
#include "vga.h"

#include <stdint.h>
#include <stddef.h>

#include "io.h"

void vga_disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void vga_clear()
{
    volatile vga_cell* video_mem = (vga_cell*)0xB8000;
    size_t video_mem_len = 80 * 25;
    for (size_t i = 0; i < video_mem_len; i++)
    {
        video_mem[i].ascii = ' ';
        video_mem[i].color = 0x0F;
    }
}

void vga_write_str_at(char* input, uint8_t x, uint8_t y)
{
    volatile vga_cell* video_mem = (vga_cell*)0xB8000;

    char* ptr = input;
    uint8_t offset = 0;

    while (*ptr != '\0')
    {
        video_mem[(x + offset) + 80 * y].ascii = *ptr;
        video_mem[(x + offset) + 80 * y].color = 0x0A;

        offset++;
        ptr++;
    }
}
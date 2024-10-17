#include "vga.h"

#include <stdint.h>
#include <stddef.h>

#include "io.h"

void vga_disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void vga_enable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | 14);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
}

void vga_set_cursor_position(uint8_t x, uint8_t y)
{
    uint16_t pos = y * 80 + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void vga_clear(vga_color bg, vga_color fg)
{
    volatile vga_cell *video_mem = (vga_cell *)0xB8000;
    size_t video_mem_len = 80 * 25;
    for (size_t i = 0; i < video_mem_len; i++)
    {
        video_mem[i].ascii = ' ';
        video_mem[i].color = bg << 4 | fg;
    }
}

int vga_write_char_at(char input, uint8_t x, uint8_t y, vga_color bg, vga_color fg)
{
    char buf[2] = { input, '\0' };
    return vga_write_str_at(buf, x, y, bg, fg);
}

int vga_write_str_at(char *input, uint8_t x, uint8_t y, vga_color bg, vga_color fg)
{
    if (input == NULL)
    {
        vga_set_cursor_position(x, y);
        return x;
    }

    volatile vga_cell *video_mem = (vga_cell *)0xB8000;

    char *ptr = input;
    uint8_t xi = x;
    uint8_t yi = y;

    while (*ptr)
    {
        if ((xi + 80 * yi) >= 80 * 25 * sizeof(vga_cell))
        {
            break;
        }

        if (xi > 80)
        {
            xi = 0 + (xi % 80);
        }
        else if (yi > 25)
        {
            yi = 0 + (yi % 25);
        }

        switch (*ptr)
        {
            case '\t':
                xi += 4;
                ptr++;
                break;
            case '\n':
                yi++;
                ptr++;
                break;
            case '\r':
                xi = 0;
                ptr++;
                break;
            case '\a':
                speaker_play(500);
                speaker_stop();
                ptr++;
                break;
            case '\b':
                xi--;
                ptr++;
            case '\f':
                yi++;
                ptr++;
            default:
                video_mem[(xi) + 80 * yi].ascii = *ptr;
                video_mem[(xi) + 80 * yi].color = ((bg << 4) | fg);

                xi++;
                ptr++;
                break;
        }
    }

    vga_set_cursor_position(xi, yi);

    return xi;
}

int vga_char_at(char c, uint8_t x, uint8_t y, vga_color bg, vga_color fg)
{
    if (c == '\0')
    {
        vga_set_cursor_position(x, y);
        return x;
    }

    volatile vga_cell *video_mem = (vga_cell *)0xB8000;

    uint8_t xi = x;
    uint8_t yi = y;

        if ((xi + 80 * yi) >= 80 * 25 * sizeof(vga_cell))
        {
            return xi;
        }

        if (xi > 80)
        {
            xi = 0 + (xi % 80);
        }
        else if (yi > 25)
        {
            yi = 0 + (yi % 25);
        }

        switch (c)
        {
            case '\t':
                xi += 4;
                break;
            case '\n':
                yi++;
                break;
            case '\r':
                xi = 0;
                break;
            case '\a':
                speaker_play(500);
                speaker_stop();
                break;
            case '\b':
                xi--;
            case '\f':
                yi++;
            default:
                video_mem[(xi) + 80 * yi].ascii = c;
                video_mem[(xi) + 80 * yi].color = ((bg << 4) | fg);

                xi++;
                break;
        }

    vga_set_cursor_position(xi, yi);

    return xi;
}

vga_cell* vga_get_vram_ptr()
{

}
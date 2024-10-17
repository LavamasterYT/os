#include "tty.h"

#include "vga.h"
#include "string.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

uint8_t bg;
uint8_t fg;

void tty_init()
{
    bg = VGA_BLACK;
    fg = VGA_GRAY;
}

uint16_t get_cursor_position(void)
{
    uint16_t cpos = 0;
    outb(0x3D4, 0x0F);
    cpos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    cpos |= ((uint16_t)inb(0x3D5)) << 8;
    return cpos;
}

void tty_put(char c)
{
    int pos = get_cursor_position();

    char tbuf[20];
    volatile vga_cell *vram = (vga_cell *)0xB8000;

    int y = pos / 80;
    int x = pos % 80;

    switch (c)
    {
        case '\t':
            pos += 4;
            break;
        case '\n':
            pos += 80;
            break;
        case '\r':
            pos = 80 * y;
            break;
        case '\a':
            speaker_play(500);
            speaker_stop();
            break;
        case '\b':
            break;   
        case '\f':
            break;
        default:
            vram[pos].ascii = c;
            vram[pos].color = (bg << 4) | fg;
            pos++;
            break;
    }

    if (pos > TTY_BUFFER_LEN - 1)
    {
        memcpy(vram, vram + 80, 80 * 24 * sizeof(vga_cell));
        pos = 80 * 24 + 1;
        
        for (int x = 0; x < 80; x++)
        {
            vram[x + 80 * 24].ascii = ' ';
            vram[x + 80 * 24].color = 0x0F;
        }
    }

    vga_set_cursor_position(pos % 80, pos / 80);
}

void tty_write(const char* str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        tty_put(str[i]);
    }
}

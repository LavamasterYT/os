#include "tty.h"

#include "vga.h"
#include "string.h"

int c = 0;
vga_color bg = VGA_BLACK;
vga_color fg = VGA_WHITE;

void tty_put(char c)
{
    vga_cell* vram = vga_get_vram_ptr();

    int x = c % 25;
    int y = c / 25;

    if (y > 25)
    {
        
    }

    switch (c)
    {
        case '\t':
            c += 4;
            break;
        case '\n':
            
            break;
        case '\r':
            
            break;
        case '\a':
            speaker_play(500);
            speaker_stop();
            break;
        case '\b':
            
        case '\f':
            
        default:
            vram[c].ascii = c;
            vram[c].color = bg << 4 | fg;
            c++;
            break;
    }
}

void tty_write(const char* str)
{

}

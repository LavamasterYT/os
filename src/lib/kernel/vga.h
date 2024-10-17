#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include "io.h"

typedef struct
{
    uint8_t ascii;
    uint8_t color;
} vga_cell __attribute__((packed));

typedef enum
{
    VGA_BLACK,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_BROWN,
    VGA_GRAY,
    VGA_DARKGRAY,
    VGA_LIGHTBLUE,
    VGA_LIGHTGREEN,
    VGA_LIGHTCYAN,
    VGA_LIGHTRED,
    VGA_LIGHTMAGENTA,
    VGA_YELLOW,
    VGA_WHITE
} vga_color;

void vga_enable_cursor();
void vga_disable_cursor();
void vga_set_cursor_position(uint8_t x, uint8_t y);
void vga_clear(vga_color bg, vga_color fg);
int vga_write_char_at(char input, uint8_t x, uint8_t y, vga_color bg, vga_color fg);
int vga_write_str_at(char* input, uint8_t x, uint8_t y, vga_color bg, vga_color fg);
int vga_char_at(char c, uint8_t x, uint8_t y, vga_color bg, vga_color fg);
vga_cell* vga_get_vram_ptr();

#endif
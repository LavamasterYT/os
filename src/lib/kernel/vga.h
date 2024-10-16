#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include "io.h"

typedef struct
{
    uint8_t ascii;
    uint8_t color;
} vga_cell __attribute__((packed));

void vga_enable_cursor();
void vga_disable_cursor();
void vga_set_cursor_position(uint8_t x, uint8_t y);
void vga_clear();
int vga_write_str_at(char* input, uint8_t x, uint8_t y);
#endif
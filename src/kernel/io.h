#ifndef IO_H
#define IO_H

#include <stdint.h>

void outb(uint16_t io, uint8_t value);
uint8_t inb(uint16_t io);

#endif
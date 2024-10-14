#include "io.h"

#include <stdint.h>

void outb(uint16_t io, uint8_t value)
{
    asm volatile(
    "outb %0, %1"
    :
    : "a"(value), "d"(io)
    );
}
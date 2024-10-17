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

uint8_t inb(uint16_t io)
{
    uint8_t ret;

    asm volatile(
        "in %%dx, %%al"
        :
        "=a"(ret)
        :
        "d"(io)
        :
        "memory"
    );

    return ret;
}

uint8_t old43;
uint8_t old42;

void speaker_play(uint32_t freq)
{
    uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / freq;

    old43 = inb(0x43);
    old42 = inb(0x42);

 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
}

void speaker_stop()
{
 	uint8_t tmp = inb(0x61) & 0xFC;
 	outb(0x61, tmp);

    outb(0x43, old43);
    outb(0x42, old42);
}
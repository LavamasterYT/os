#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

typedef struct
{
    uint64_t base_addr;
    uint64_t len;
    uint32_t type;
    uint32_t acpi;
} nmap __attribute__((packed));



#endif
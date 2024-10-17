#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    uint64_t base_addr;
    uint64_t len;
    uint32_t type;
    uint32_t acpi;
} nmap __attribute__((packed));

int init_memory(nmap* map, int len);
void* get_next_free(size_t len);

#endif
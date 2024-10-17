#include "memory.h"

#include <stddef.h>
#include <stdio.h>

void* mem_base = NULL;
uint64_t mem_c = 0;
uint64_t mem_size = 0;

int init_memory(nmap* map, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (map[i].base_addr >= 0x100000 && map[i].type == 1)
        {
            mem_base = (void*)map[i].base_addr;
            mem_size = map[i].len;
            mem_c = 0;

            return 0;
        }
    }

    return 1;
}

void* get_next_free(size_t len)
{
    if ((mem_c + len) >= mem_size)
    {
        return NULL;
    }
    else
    {
        void* ret = mem_base;
        mem_base = (char*)mem_base + len;
        mem_c += len;
        printf("Allocated memory at: %p\n", ret);
        return ret;
    }
}
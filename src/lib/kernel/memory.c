#include "memory.h"

#include <stddef.h>

void* base = NULL;
uint64_t c = 0;
uint64_t size = 0;

int init_memory(nmap* map, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (map[i].base_addr >= 0x100000 && map[i].type == 1)
        {
            base = (void*)map[i].base_addr;
            size = map[i].len;
            c = 0;
            return 0;
        }
    }

    return 1;
}

void* get_next_free(size_t len)
{
    if ((c + len) >= size)
    {
        return NULL;
    }
    else
    {
        void* ret = base;
        base = (char*)base + len;
        c += len;
        return ret;
    }
}
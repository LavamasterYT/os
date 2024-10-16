#include "string.h"

void* memchr(const void* ptr , int c, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (((char*)ptr)[i] == c)
            return &((char*)ptr)[i];
    }
    
    return NULL;
}

int memcmp(const void* ptr1, const void* ptr2, size_t n)
{
    return 0;
}

void* memcpy(void *dest, const void* src, size_t n)
{
    return NULL;
}

void* memmove(void *dest, const void* src, size_t n)
{
    return NULL;
}

void* memset(void* ptr, int c, size_t n)
{
    return NULL;
}

char* strcat(char* dest, const char* src)
{
    return NULL;
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;

    return len;
}

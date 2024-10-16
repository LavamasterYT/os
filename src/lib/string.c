#include "string.h"

void* memchr(const void* str , int c, size_t n)
{
    void* ptr = str;

    for (size_t i = 0; i < n; i++)
    {
        if (*(char*)ptr == '\0') // If end of string
            break;

        if (*(char*)ptr == c)
            return ptr;

        ptr++;
    }
    
    return NULL;
}

int memcmp(const void* str1, const void* str2, size_t n)
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

void* memset(void* str, int c, size_t n)
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

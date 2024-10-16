#ifndef STRING_H
#define STRING_H

#include <stddef.h>

#ifndef NULL
#define NULL 0
#endif

void* memchr(const void* str , int c, size_t n);
int memcmp(const void* str1, const void* str2, size_t n);
void* memcpy(void *dest, const void* src, size_t n);
void* memmove(void *dest, const void* src, size_t n);
void* memset(void* str, int c, size_t n);
char* strcat(char* dest, const char* src);

#endif
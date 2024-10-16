#ifndef STRING_H
#define STRING_H

#include <stddef.h>

#ifndef NULL
#define NULL 0
#endif

/**
 * Searches for the first occurrence of the value c in 
 * the first n bytes of the buffer pointed to.
 * 
 * @param str Pointer to buffer
 * @param c Character to find
 * @param n Number of bytes to be analyzed
 * @return Pointer to matching byte or NULL if nothing found.
 */
void* memchr(const void* ptr, int c, size_t n);

/**
 * Compares two blocks of memory.
 * 
 * @param ptr1 Pointer to first block of memory
 * @param ptr2 Pointer to second block of memory
 * @param n Number of bytes to compare
 * @return An integral value indicating the relationship between the memory blocks.
 *         A return value of 0 indicates that both memory blocks are equal.
 *         A return value of < 0 indicates that the first byte that does not match has a lower value in ptr1 than in ptr2
 *         A return value of > 0 indicates that the first byte that does not match has a greater value in ptr than in ptr2
 */
int memcmp(const void* ptr1, const void* ptr2, size_t n);


void* memcpy(void *dest, const void* src, size_t n);
void* memmove(void *dest, const void* src, size_t n);
void* memset(void* str, int c, size_t n);
char* strcat(char* dest, const char* src);

/**
 * Gets the length of a null terminated string buffer.
 * 
 * @param str Pointer to string
 * @return Length of string.
 */
size_t strlen(const char* str);

#endif
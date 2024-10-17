#ifndef STDLIB_H
#define STDLIB_H

#include "stddef.h"

/**
 * Converts an integer value to a null terminated string using the
 * specified base and stores the result in str.
 * 
 * @param value The integer value
 * @param str The string buffer to store the result
 * @param base The base to convert to
 * @return The pointer where the result is stored, same as str
 */
char* itoa(int value, char* str, int base);

int atoi(const char* str);

/**
 * Converts an long value to a null terminated string using the
 * specified base and stores the result in str.
 * 
 * @param value The long value
 * @param str The string buffer to store the result
 * @param base The base to convert to
 * @return The pointer where the result is stored, same as str
 */
char* ultoa(unsigned long int value, char* str, int base);
char* ulltoa(unsigned long long int value, char* str, int base);
char* uitoa(unsigned int value, char* str, int base);
char* uhtoa(unsigned short int value, char* str, int base);
char* uhhtoa(unsigned char value, char* str, int base);

void* malloc(size_t len);

#endif
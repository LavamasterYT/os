#ifndef STDLIB_H
#define STDLIB_H

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

/**
 * Converts an long value to a null terminated string using the
 * specified base and stores the result in str.
 * 
 * @param value The long value
 * @param str The string buffer to store the result
 * @param base The base to convert to
 * @return The pointer where the result is stored, same as str
 */
char* ultoa(unsigned long value, char* str, int base);

#endif
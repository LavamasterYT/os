#include "stdio.h"

#include <stdarg.h>
#include "stdlib.h"

#include <kernel/vga.h>
#include <kernel/tty.h>
#include "string.h"

int printf(const char* str, ...)
{
    va_list list;
    va_start(list, str);

    int hit_format = 0;
    int hit_precision = 0;
    int hit_leading_zeros = 0;
    int hit_pad_spaces = 0;
    int hit_prefix = 0;
    int padding = 0;
    int longs = 0;

    char token[256];
    char buffer[16];
    int token_index = 0;
    
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (hit_format)
        {
            if (str[i] == '%')
            {
                hit_format = 0;
                tty_put('%');
            }
            else if (str[i] == 's')
            {
                hit_format = 0;
                tty_write(va_arg(list, char*));
            }
            else if (str[i] == 'c')
            {
                hit_format = 0;
                tty_write(va_arg(list, char));
            }
            else if (str[i] == 'p')
            {
                hit_format = 0;
                tty_write(itoa(va_arg(list, unsigned int), buffer, 16));
            }
            else if (str[i] == 'd' | str[i] == 'i')
            {
                hit_format = 0;
                tty_write(itoa(va_arg(list, int), buffer, 10));
            }
            else if (str[i] == 'x')
            {
                if (longs == 2)
                    ulltoa(va_arg(list, unsigned long long int), buffer, 16);
                else if (longs == 1)
                    ultoa(va_arg(list, unsigned long int), buffer, 16);
                else if (longs == 0)
                    uitoa(va_arg(list, unsigned int), buffer, 16);

                longs = 0;
                hit_format = 0;

                if (hit_prefix)
                    tty_write("0x");
                if (hit_precision)
                {
                    token[token_index] = '\0';
                    token_index = 0;
                    padding = atoi(token) - strlen(buffer);
                    for (padding > 0; padding--;)
                        tty_put('0');
                    hit_precision = 0;
                }
                tty_write(buffer);
            }
            else if (str[i] == 'o')
            {
                hit_format = 0;
                tty_write(itoa(va_arg(list, unsigned int), buffer, 8));
            }
            else if (str[i] == 'u')
            {
                hit_format = 0;
                tty_write(itoa(va_arg(list, unsigned int), buffer, 10));
            }
            else if (str[i] == '.')
            {
                hit_precision = 1;
            }
            else if (str[i] == '0' && !hit_leading_zeros)
            {
                hit_leading_zeros = 1;
            }
            else if (str[i] == ' ')
            {
                hit_pad_spaces = 1;
            }
            else if (str[i] == '#')
            {
                hit_prefix = 1;
            }
            else if (str[i] == 'l')
            {
                longs++;
            }
            else if (str[i] == 'h')
            {
                longs--;
            }
            else if (str[i] >= '0' && str[i] <= '9')
            {
                token[token_index++] = str[i];
            }
        }
        else if (str[i] == '%')
        {
            token[token_index] = '\0';
            token_index = 0;
            tty_write(token);
            hit_format = 1;
        }
        else if (str[i] == '\n')
        {
            token[token_index++] = '\n';
            token[token_index++] = '\r';
        }
        else
            token[token_index++] = str[i];
    }

    token[token_index] = '\0';
    tty_write(token);

    va_end(list);
}
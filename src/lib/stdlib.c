#include "stdlib.h"

#include "string.h"

char* itoa(int value, char* str, int base)
{
    char* ptr = str;
    int neg = value < 0 && base == 10 ? 1 : 0;

    value = neg ? -value : value;

    if (value == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    int r;
    int d = value;

    while (d != 0)
    {
        r = d % base;
        d = d / base;

        if (r > 9)
            *ptr = 'a' + (r - 10);
        else
            *ptr = '0' + r;

        ptr++;
    }

    if (neg)
    {
        *ptr = '-';
        ptr++;
    }
    *ptr = '\0';

    int i = 0;
    int j = strlen(str) - 1;

    while (i < j)
    {
        char t = str[i];
        str[i] = str[j];
        str[j] = t;
        j--;
        i++;
    }
    
    return str;
}

char* ultoa(unsigned long value, char* str, int base)
{
    char* ptr = str;
    int neg = value < 0 && base == 10 ? 1 : 0;

    value = neg ? -value : value;

    if (value == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    unsigned long r;
    unsigned long d = value;

    while (d != 0)
    {
        r = d % base;
        d = d / base;

        if (r > 9)
            *ptr = 'a' + (r - 10);
        else
            *ptr = '0' + r;

        ptr++;
    }

    if (neg)
    {
        *ptr = '-';
        ptr++;
    }
    *ptr = '\0';

    int i = 0;
    int j = strlen(str) - 1;

    while (i < j)
    {
        char t = str[i];
        str[i] = str[j];
        str[j] = t;
        j--;
        i++;
    }
    
    return str;
}
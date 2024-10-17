#include "stdlib.h"

#include <kernel/memory.h>

#include "string.h"

void* malloc(size_t len)
{
    return get_next_free(len);
}

int atoi(const char* str)
{
    size_t len = strlen(str);
    int base = 1;
    int ret = 0;

    for (int i = len - 1; i >= 0; i--)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            int c = str[i] - '0';

            ret += c * base;

            base *= 10;
        }
    }

    return ret;
}

char* ultoa(unsigned long int value, char* str, int base)
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

    unsigned long int r;
    unsigned long int d = value;

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

char* ulltoa(unsigned long long int value, char* str, int base)
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

    unsigned long int r;
    unsigned long int d = value;

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

char* uitoa(unsigned int value, char* str, int base)
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

    unsigned int r;
    unsigned int d = value;

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

char* uhtoa(unsigned short int value, char* str, int base)
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

    unsigned short int r;
    unsigned short int d = value;

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

char* uhhtoa(unsigned char value, char* str, int base)
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

    unsigned char r;
    unsigned char d = value;

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

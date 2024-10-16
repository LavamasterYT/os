#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
    char buffer[256];

    printf("%s\n", itoa(10, buffer, 10));
    return 0;
}
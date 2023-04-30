#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void codecA(char* str)
{
    int index = 0;
    while (str[index] != '\0')
    {
        if (str[index] >= 'A' && str[index] <= 'Z')
        {
            str[index] = str[index] - 'A' + 'a';
        }
        index++;
    }
}
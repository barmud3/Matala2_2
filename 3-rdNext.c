#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void codecB(char* str)
{
    int index = 0;
    while (str[index] != '\0')
    {
        str[index] += 3;
        index++;
    }
}

void codecBReverse(char* str)
{
    int index = 0;
    while (str[index]!='\0')
    {
        str[index] -= 3;
        index++;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdbool.h>


void (*codecA)(char*);
void (*codecBReverse)(char*);

bool init_library()
{
    void* hdl1 = dlopen("./libcodecA.so",RTLD_LAZY);
    void* hdl2 = dlopen("./libcodecB.so",RTLD_LAZY);
    if (NULL == hdl1 || NULL == hdl2)
    {
        return false;
    }
    codecA = (void(*)(char*))dlsym(hdl1,"codecA");
    codecBReverse = (void(*)(char*))dlsym(hdl2,"codecBReverse");
    if (NULL == codecA || NULL == codecBReverse)
    {
        return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("You didn't enter correct input , suppose to be : ./decode [codecA/codecB] [message] \n");
        return 1;
    }
    char* str = malloc(sizeof(argv[2]));
    if(strcmp(argv[1],"codecA") == 0 && init_library())
    {
        strcpy(str,argv[2]);
        codecA(str);
        printf("%s\n",str);
    }
    if(strcmp(argv[1],"codecB") == 0 && init_library())
    {
        strcpy(str,argv[2]);
        codecBReverse(str);
        printf("%s\n",str);
    }
    free(str);
    return 0;
}
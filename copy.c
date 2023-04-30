#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int copyFunc(FILE* f1 , FILE* f2)
{
    char f1C = getc(f1);
    while (f1C != EOF)
    {
        fprintf(f2,"%c",f1C);
        f1C = getc(f1);
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    if(argc < 3 || argc > 5)
    {
        printf("Wrong using of the tool , suppose to be : ./copy <file1> <file2> -v/-f\n");
        return 1;
    }
    FILE* f1 = fopen(argv[1],"r");
    FILE* f2 = fopen(argv[2],"a");
    if (f1 == NULL || f2 == NULL)
    {
        printf("File not found/cann't be open\n");
        exit(1);
    }
    if (argc == 3) //without flags
    {
        int result = copyFunc(f1,f2);
        return result;
    }
    
    const char* specailFlag1 = argv[3];
    const char* specailFlag2;
    if (argc == 5)
    {
        specailFlag2 = argv[4];
    }
    else{
        specailFlag2 = "temp";
    }
    if (strcmp(specailFlag1,"-f") == 0 || strcmp(specailFlag2,"-f") == 0)
    {
        f2 = fopen(argv[2],"w");
    }
    int result = copyFunc(f1,f2);
    if(strcmp(specailFlag1,"-v") == 0 || strcmp(specailFlag2,"-v") == 0)
    {
        switch (result)
        {
        case 1:
            printf("Success\n");
            break;
        
        case 0:
            printf("Fail\n");
            break;
        }
    }
    return result;
}
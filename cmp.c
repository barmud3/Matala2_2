#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int compareFile(FILE* f1 , FILE* f2 , int sensetive)
{
    char f1C = getc(f1);
    char f2C = getc(f2);
    while (f1C!= EOF && f2C!= EOF)
    {
        if (sensetive == 1)
        {      
            if (f1C >= 'A' && f1C <= 'Z')
            {
                f1C = f1C - 'A' + 'a';
            }
            if (f2C >= 'A' && f2C <= 'Z')
            {
                f2C = f2C - 'A' + 'a';
            }
        }
        if (f1C != f2C)
        {
            return 0;
        }
        f1C = getc(f1);
        f2C = getc(f2);
    }
    if (f1C == EOF && f2C == EOF)
    {
        return 1;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc<3 || argc>5)
    {
        printf("You didn't enter correct input , suppose to be : ./cmp <file1><file2> -v/-i \n");
        return 1;
    }
    FILE* f1 = fopen(argv[1],"r");
    FILE* f2 = fopen(argv[2],"r");
    if (f1==NULL || f2 == NULL)
    {
        printf("File not found/cann't be open\n");
        exit(1);
    }

    if (argc == 3) //without flags
    {
        int result = compareFile(f1,f2,0);
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
    
    int result = -1;
    if (strcmp(specailFlag1 ,"-i") == 0 || strcmp(specailFlag2 ,"-i") == 0)
    {
        result = compareFile(f1,f2,1); //compare file with case sensetive
    }
    if (strcmp(specailFlag1,"-v") == 0 || strcmp(specailFlag2,"-v") == 0)
    {
        if (result==-1)
        {     
        result = compareFile(f1,f2,0); //compare file without case sensetive
        }
        switch (result)
        {
        case 0:
            printf("distinct\n");
            break;
        
        case 1:
            printf("equal\n");
            break;
        }
    }

    if (fclose(f1) !=0 || fclose(f2)!=0)
    {
        printf("Error closing files");
    }
    
    return result;
}

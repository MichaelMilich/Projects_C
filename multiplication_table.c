#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[])
{
    // this is a comment
    // first we must check if there is input of 1 varaible
    if (argc != 2)
    {
        printf("please insert one input to the program %s", argv[0]);
        return 1;
    }
    // next, check if the input is 0. - special case.
    if (strcmp(argv[1], "0") == 0)
    {
        printf("The input is zero.\n");
        return 0;
    }
    char *endptr = 1;
    float fnum = strtof(argv[1], &endptr);
    /*Print the value pointed to by endptr*/
    printf("Value:  %d\n", *endptr);

    /*Print the address pointed to by endptr*/
    printf("address pointed by endptr:  %p\n", endptr);

    /*Print the address of iptr itself*/
    printf("adress of endptr itself:  %p\n", &endptr);

    if (*endptr != 0)
    {
        printf("invalid input, '%s' is not integer or float", argv[1]);
        return 1;
    }
    int inum = (int)fnum;
    if (fnum == (float)inum)
    {
        printf("The input is integer");
        int res;
        for (int i = 0; i <= 10; ++i)
        {
            res = inum * i;
            printf("multiplication of %d by %d = %d \n", inum, i, res);
        }
    }
    else
    {
        printf("The input is float");
        float res;
        for (int i = 0; i <= 10; ++i)
        {
            res = fnum * i;
            printf("multiplication of %f by %d = %f \n", fnum, i, res);
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "r");
    FILE *fw = fopen(argv[3], "w");
    //FILE *f1 = fopen("input1.txt", "r");
    //FILE *f2 = fopen("input2.txt", "r");
    //FILE *fw = fopen("q8_ans.txt", "w");

    char a[25], b[25];
    short int a1 = 0, b1 = 0;

    while (a1 != -1 || b1 != -1)
    {
        if (a1 == 0)
        {
            if (fscanf(f1, "%s", a) != EOF)
            {
                a1 = 1;
            }
            else
                a1 = -1;
        }
        if (b1 == 0)
        {
            if (fscanf(f2, "%s", b) != EOF)
            {
                b1 = 1;
            }
            else
                b1 = -1;
        }
        if (a1 == -1 && b1 == -1)
            break;
        else if (a1 == -1)
        {
            fprintf(fw, "%s\n", b);
            b1 = 0;
        }
        else if (b1 == -1)
        {
            fprintf(fw, "%s\n", a);
            a1 = 0;
        }
        else if (strcmp(a, b) < 0)
        {
            fprintf(fw, "%s\n", a);
            a1 = 0;
        }
        else
        {
            fprintf(fw, "%s\n", b);
            b1 = 0;
        }
    }
    fclose(f1);
    fclose(f2);
    fclose(fw);
    return 0;
}
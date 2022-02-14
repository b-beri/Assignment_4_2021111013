#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char words[1000][25];
int frequency[1000];
int n=0;

void stringSort(char names[][25], int numofnames)
{
    int swap_count = 0;
    char tempstr[25];

    if (numofnames == 1)
        return;

    for (int i = 0; i < numofnames - 1; i = i + 1)
    {
        if (strcmp(&names[i][0], &names[i + 1][0]) < 0)
        {
            continue;
        }
        else
        {
            strcpy(tempstr, &names[i][0]);
            strcpy(&names[i][0], &names[i + 1][0]);
            strcpy(&names[i + 1][0], tempstr);

            int temp = frequency[i];
            frequency[i]=frequency[i+1];
            frequency[i+1]=temp;

            ++swap_count;
        }
    }

    if (swap_count > 0)
        stringSort(names, numofnames - 1);
}

void calculate(FILE *fp)
{
    char c[25];
    while (fscanf(fp, "%s", c) != EOF)
    {
        short int flag=0;
        for(int i=0;i<n;i++)
        {
            if(0==strcmp(words[i],c))
            {
                flag=1;
                frequency[i]++;
            }
        }
        if (!flag)
        {
            strcpy(words[n],c);
            frequency[n]=1;
            n++;
        }
    }
}

void write(FILE *fp)
{
    for (int i=0;i<n;i++)
    {
        fprintf(fp,"%s:%d\n",words[i],frequency[i]);
    }
}

int main(int argc, char *argv[])
{
    FILE *fw = fopen(argv[1], "w");

    for (int i = 2; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        calculate(fp);
        fclose(fp);
    }
    write(fw);
    fclose(fw);
    return 0;
}
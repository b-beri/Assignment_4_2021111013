#include <stdio.h>
#include <stdlib.h>

long long count[62];

long long calculate(FILE *fp)
{
    char c;
    while (fscanf(fp, "%c", &c) != EOF)
    {
        if (c >= '0' && c <= '9')
        {
            count[c - '0']++;
        }
        else if (c >= 'A' && c <= 'Z')
        {
            count[c - 'A' + 9]++;
        }
        else if (c >= 'a' && c <= 'a')
        {
            count[c - 'a' + 35]++;
        }
    }
}

void write(FILE *fp)
{
    for (int i = 0; i < 62; i++)
    {
        if (i < 10)
        {
            fprintf(fp, "%c:%lld\n", i + '0', count[i]);
        }
        else if (i < 36)
        {
            fprintf(fp, "%c:%lld\n", i + 'A' - 10, count[i]);
        }
        else
        {
            fprintf(fp, "%c:%lld\n", i + 'a' - 36, count[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 62; i++)
        count[i] = 0;

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
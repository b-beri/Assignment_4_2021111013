#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fr = fopen(argv[1], "r");
    FILE *fm = fopen(argv[2], "r");
    FILE *fw1 = fopen(argv[3], "w");
    //FILE *fr = fopen("data.txt", "r");
    //FILE *fm = fopen("mean.txt", "r");
    //FILE *fw1 = fopen("4c.txt", "w");

    long double mean;
    fscanf(fm, "%Lf", &mean);

    double a = 0.8 * mean, b = 1.2 * mean, r;
    double count = 0,n=0;

    while (fscanf(fr, "%lf", &r) != EOF)
    {
        n++;
        if (a <= r && r <= b)
            count++;
    }

    long double percent = (count*100)/n;

    fprintf(fw1, "%Lf", percent);

    fclose(fw1);
    fclose(fm);
    fclose(fr);
    return 0;
}
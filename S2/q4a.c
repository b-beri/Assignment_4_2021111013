#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fr=fopen(argv[1],"r");
    FILE *fw=fopen(argv[2],"w");

    long double sum=0,a;
    long int count=0;

    while(fscanf(fr, "%Lf", &a) != EOF) {
        count++;
        sum+=a;
    }

    long double mean = sum/count;

    fprintf(fw,"%Lf",mean);

    fclose(fw);
    fclose(fr);
    return 0;
}
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define NumOfTerms 10 // 1000000

long double RandomNumberGenerator(const int nNumOfNumsToGenerate)
{
    float nRandonNumber1 = 0, nRandonNumber2 = 0;
    long double total_count = 0, in_count = 0;

    for (int i = 0; i < nNumOfNumsToGenerate; i++)
    {
        nRandonNumber1 = (float)rand() / (float)(RAND_MAX / 2);
        nRandonNumber2 = (float)rand() / (float)(RAND_MAX / 2);
        nRandonNumber1--;
        nRandonNumber2--;

        //printf("%.3f %.3f\n", nRandonNumber1, nRandonNumber2);

        total_count++;
        if (nRandonNumber1 * nRandonNumber1 + nRandonNumber2 * nRandonNumber2 <= 1)
            in_count++;
    }
    //printf("%Lf %Lf %Lf\n",in_count,total_count, 4.0*(in_count/total_count));
    
    return 4.0*(in_count/total_count);
}

void fileWrite()
{
    FILE *fp = fopen("q3.data", "w");

    for (int i = 100; i <= 1000; i+=100)
    {
        //printf("%s %lld\n", &names[i][0], count[i]);
        fprintf(fp, "%d %Lf %.5lf\n", i,RandomNumberGenerator(i),3.14159);
    }
    fclose(fp);
}

void main()
{
    srand(time(NULL));
    RandomNumberGenerator(NumOfTerms);
    fileWrite();
    system("gnuplot gnucode.txt");
}
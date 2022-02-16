#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fr = fopen(argv[1], "r");
    FILE *fm = fopen(argv[2], "r");
    FILE *fw1 = fopen(argv[3], "w");
    FILE *fw2 = fopen("q4b.data", "w");

    long double mean;
    fscanf(fm, "%Lf", &mean);

    long double sum_square = 0, sum = 0;

    long double a;
    int count = 0;

    while (fscanf(fr, "%Lf", &a) != EOF)
    {
        count++;
        sum_square += (a * a);
        sum += a;
        long double actual_variance = sum_square / count - (sum / count) * (sum / count);
        if (count != 1)
        {
            long double approx_variance = sum_square / (count - 1) - (sum * sum) / (count * (count - 1));
            fprintf(fw2, "%d %.5Lf %.5Lf\n", count, actual_variance, approx_variance);
        }
    }

    double variance = sum_square / count - (sum / count) * (sum / count);

    fprintf(fw1, "%lf", variance);

    fclose(fw1);
    fclose(fw2);
    fclose(fm);
    fclose(fr);

    char *gnuplot_cmd = (char *)malloc(50 * sizeof(char));
    sprintf(gnuplot_cmd, "gnuplot -e \"variance = '%lf'\" gnucode.txt", variance);

    //system("gnuplot gnucode.txt");
    system(gnuplot_cmd);

    return 0;
}
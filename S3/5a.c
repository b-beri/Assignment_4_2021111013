#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calculate()
{
    long int a = random(), b = random(), c = random(), d = random();

    double count_seed_0 = 0, count_seed_1 = 0, count_rand_0 = 0, count_rand_1 = 0;

    char seed1[1000001], seed2[1000001];

    for (int i = 0; i < 32; i++)
    {
        seed1[i] = a % 2;
        a /= 2;

        seed1[i + 32] = b % 2;
        b /= 2;

        seed1[i + 64] = c % 2;
        c /= 2;

        seed1[i + 96] = d % 2;
        d /= 2;
    }

    for (long int i = 128; i < 1000000; i++)
    {
        seed1[i] = seed1[i - 1] ^ seed1[i - 127];

        if ((int)seed1[i] == 1)
        {
            count_seed_1++;
        }
        else if ((int)seed1[i] == 0)
        {
            count_seed_0++;
        }

        seed2[i] = rand() % 2;

        if ((int)seed2[i] == 1)
        {
            count_rand_1++;
        }
        else if ((int)seed2[i] == 0)
        {
            count_rand_0++;
        }
    }
    double prob_seed_0 = count_seed_0 * 100 / (1000000 - 127);
    double prob_seed_1 = count_seed_1 * 100 / (1000000 - 127);
    double prob_rand_0 = count_rand_0 * 100 / (1000000 - 127);
    double prob_rand_1 = count_rand_1 * 100 / (1000000 - 127);

    printf("Via XORing Random Seed\n0 -> %lf\n1 -> %lf\n", prob_seed_0, prob_seed_1);
    printf("Via Random\n0 -> %lf\n1 -> %lf\n", prob_rand_0, prob_rand_1);
}

int main()
{
    srand(time(NULL));
    srandom(time(NULL));
    calculate();

    return 0;
}
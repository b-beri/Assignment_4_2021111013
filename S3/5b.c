#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calculate()
{
    long int a = random(), b = random(), c = random(), d = random();

    double count_xor_0_0 = 0, count_xor_0_1 = 0, count_rand_0_0 = 0, count_rand_0_1 = 0;

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
    seed2[127] = rand() % 2;

    for (long int i = 128; i < 1000000; i++)
    {
        seed1[i] = seed1[i - 1] ^ seed1[i - 127];
        seed2[i] = rand() % 2;

        if (seed1[i - 1] == 0 && seed1[i] == 0) // checking the probability x1 = 0 / xi-1 = 0 for XOR method
		{
			count_xor_0_0++;
		}
		if (seed1[i - 1] == 1 && seed1[i] == 0) // checking the probability x1 = 0 / xi-1 = 1 for XOR method
		{
			count_xor_0_1++;
		}

		if (seed2[i - 1] == 0 && seed2[i] == 0) // checking the probability x1 = 0 / xi-1 = 0 for rand % 2 method
		{
			count_rand_0_0++;
		}
		if (seed2[i - 1] == 1 && seed2[i] == 0) // checking the probability x1 = 0 / xi-1 = 1 for rand % 2 method
		{
			count_rand_0_1++;
		}
    }
    printf("%lf\n", count_xor_0_0 / (1000000-127));
	printf("%lf\n", count_xor_0_1 / (1000000-127));
	printf("%lf\n", count_rand_0_0 / (1000000-127));
	printf("%lf\n", count_rand_0_1 / (1000000-127));
}

int main()
{
    srand(time(NULL));
    srandom(time(NULL));
    calculate();

    return 0;
}
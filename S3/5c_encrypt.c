#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calculate_key(FILE *fp, char seed[])
{
    long int a = random(), b = random(), c = random(), d = random();

    for (int i = 0; i < 32; i++)
    {
        seed[i] = (a % 2);
        a /= 2;

        seed[i + 32] = (b % 2);
        b /= 2;

        seed[i + 64] = (c % 2);
        c /= 2;

        seed[i + 96] = (d % 2);
        d /= 2;
    }
    for (int i = 1; i < 128; i++)
        fprintf(fp, "%c", seed[i] + 48);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    srandom(time(NULL));
    char seed[128];
    unsigned char c;
    long int count = 127;

    FILE *fr = fopen(argv[1], "r");
    // FILE *fr = fopen("DSM.pdf", "r");

    FILE *fkey = fopen(argv[2], "w");
    // FILE *fkey = fopen("key.txt", "w");

    FILE *fw = fopen(argv[3], "w");
    // FILE *fw = fopen("encrypt.txt", "w");

    calculate_key(fkey, seed);

    while (fscanf(fr, "%c", &c) != EOF)
    {
        for (int i = 7; i >= 0; --i)
        {
            count++;
            char bit = ((c & (1 << i)) ? 1 : 0);
            if (count > 127)
            {
                if (count % 127 != 0 && (count - 1) % 127 != 0)
                    seed[count % 127] = seed[(count - 1) % 127] ^ seed[(count - 127) % 127];
                else if (count % 127 != 0 && (count - 1) % 127 == 0)
                    seed[count % 127] = seed[127] ^ seed[(count - 127) % 127];
                else
                    seed[127] = seed[(count - 1) % 127] ^ seed[127];
            }
            int mod = (count % 127 == 0) ? 127 : (count % 127);

            fprintf(fw, "%c", (bit ^ seed[mod]) + 48);
            // printf("%c %c %c\n", seed[mod]+48, bit+48, (bit ^ seed[mod]) + 48);
        }
    }

    fclose(fr);
    fclose(fw);
    return 0;
}
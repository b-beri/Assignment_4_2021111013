#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    srandom(time(NULL));
    char seed[128];
    unsigned char c;
    long int count = 127;

    FILE *fw = fopen(argv[3],"w");
    //FILE *fw = fopen("output.pdf", "w");

    FILE *fkey = fopen(argv[1],"r");
    //FILE *fkey = fopen("key.txt", "r");

    FILE *fr = fopen(argv[2],"r");
    //FILE *fr = fopen("encrypt.txt", "r");

    int j = 1;
    while (fscanf(fkey, "%c", &c) != EOF)
    {
        seed[j] = c - 48;
        j++;
    }

    char bit[8];
    j = 0;

    while (fscanf(fr, "%c", &c) != EOF)
    {
        bit[j] = c - 48;
        j++;

        if (j == 8)
        {
            unsigned char chr = 0;
            for (int k = 0; k < 8; k++)
            {
                count++;
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
                bit[k] = (bit[k] ^ seed[mod]);

                if (bit[k] == 1)
                {
                    unsigned char chr1 = 1 << (7 - k);
                    chr = chr | chr1;
                }
            }
            fprintf(fw, "%c", chr);
            j = 0;
        }
    }

    fclose(fr);
    fclose(fkey);
    fclose(fw);
    return 0;
}
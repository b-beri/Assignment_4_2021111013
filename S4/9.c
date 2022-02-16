#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000000

FILE **fps;

void stringSort(char names[][101], int numofnames)
{
    int swap_count = 0;
    char tempstr[101];

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

            ++swap_count;
        }
    }

    if (swap_count > 0)
        stringSort(names, numofnames - 1);
}

void FileSort1(long long int n)
{
    char *file_i_name = (char *)malloc(25 * sizeof(char));
    sprintf(file_i_name, "Q9_Temporary_%lld.txt", n);

    FILE *fr = fopen(file_i_name, "r");

    char data[100000][101];
    long long i = 0;
    while (fscanf(fr, "%s", data[i++]) != EOF)
        ;
    stringSort(data, --i);
    FILE *fw = fopen("TEMPORARY___.txt", "w");
    for (int j = 0; j < i; j++)
    {
        fprintf(fw, "%s\n", data[j]);
    }
    fclose(fw);

    remove(file_i_name);
    rename("TEMPORARY___.txt", file_i_name);

    free(file_i_name);
}

void FileSort2(FILE *f1, FILE *f2, FILE *fw)
{
    // FILE *f1 = fopen(argv[1], "r");
    //  FILE *f2 = fopen(argv[2], "r");
    // FILE *fw = fopen(argv[3], "w");
    //  FILE *f1 = fopen("input1.txt", "r");
    //  FILE *f2 = fopen("input2.txt", "r");
    //  FILE *fw = fopen("q8_ans.txt", "w");

    char a[101], b[101];
    short int a1 = 0, b1 = 0;

    while (a1 != -1 || b1 != -1)
    {
        if (a1 == 0)
        {
            if (fscanf(f1, "%s", a) != EOF)
            {
                a1 = 1;
            }
            else
                a1 = -1;
        }
        if (b1 == 0)
        {
            if (fscanf(f2, "%s", b) != EOF)
            {
                b1 = 1;
            }
            else
                b1 = -1;
        }
        if (a1 == -1 && b1 == -1)
            break;
        else if (a1 == -1)
        {
            fprintf(fw, "%s\n", b);
            b1 = 0;
        }
        else if (b1 == -1)
        {
            fprintf(fw, "%s\n", a);
            a1 = 0;
        }
        else if (strcmp(a, b) < 0)
        {
            fprintf(fw, "%s\n", a);
            a1 = 0;
        }
        else
        {
            fprintf(fw, "%s\n", b);
            b1 = 0;
        }
    }
    fclose(f1);
    fclose(f2);
    fclose(fw);
}

void sortAllSingleFiles(long long count_files)
{
    for (int i = 0; i <= count_files; i++)
    {
        fclose(fps[i]);
        FileSort1(i);
    }
    free(fps);
}

void sortMerge(long long count_files)
{
    count_files++;
    long long int i;
    while (count_files != 1)
    {
        for (i = 0; i < count_files && i + 1 < count_files; i += 2)
        {
            char *file_i_name = (char *)malloc(25 * sizeof(char));
            sprintf(file_i_name, "Q9_Temporary_%lld.txt", i);
            FILE *f1 = fopen(file_i_name, "r");

            char *file_i1_name = (char *)malloc(25 * sizeof(char));
            sprintf(file_i1_name, "Q9_Temporary_%lld.txt", i + 1);
            FILE *f2 = fopen(file_i1_name, "r");

            FILE *fw = fopen("TEMPORARY___.txt", "w");

            FileSort2(f1, f2, fw);

            remove(file_i_name);
            remove(file_i1_name);
            sprintf(file_i_name, "Q9_Temporary_%lld.txt", i / 2);
            rename("TEMPORARY___.txt", file_i_name);

            free(file_i_name);
            free(file_i1_name);
        }
        if (i < count_files && i + 1 == count_files)
        {
            char *file_i_name = (char *)malloc(25 * sizeof(char));
            sprintf(file_i_name, "Q9_Temporary_%lld.txt", i);
            char *file_i1_name = (char *)malloc(25 * sizeof(char));
            sprintf(file_i1_name, "Q9_Temporary_%lld.txt", i/2);

            rename(file_i_name,file_i1_name);

            free(file_i_name);
            free(file_i1_name);
        }
        if (count_files % 2 != 0)
            count_files++;
        count_files = count_files / 2;
    }
}

int main(int argc, char *argv[])
{
    //FILE *MainFile = fopen("try_data.txt", "r");
    FILE *MainFile = fopen(argv[1], "r");
    char a[101];
    fps = (FILE **)malloc(50 * sizeof(FILE *));

    long long int count = 0, count_files = 0, max_files = 50;

    fps[0] = fopen("Q9_Temporary_0.txt", "w");

    while (fscanf(MainFile, "%s", a) != EOF)
    {
        if (count < MAX_LENGTH)
        {
            fprintf(fps[count_files], "%s \n", a);
            count++;
        }
        else
        {
            if (count_files >= max_files)
            {
                max_files += 25;
                fps = (FILE **)realloc(fps, max_files * sizeof(FILE *));
            }
            count_files++;
            char *file_i_name = (char *)malloc(25 * sizeof(char));
            sprintf(file_i_name, "Q9_Temporary_%lld.txt", count_files);
            fps[count_files] = fopen(file_i_name, "w");
            fprintf(fps[count_files], "%s \n", a);
            count = 1;
            free(file_i_name);
        }
    }
    fclose(MainFile);
    sortAllSingleFiles(count_files);
    sortMerge(count_files);

    rename("Q9_Temporary_0.txt",argv[2]);

    return 0;
}
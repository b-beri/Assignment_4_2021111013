#include <time.h>
#include <stdlib.h>
#include <stdio.h>

# define NumOfTerms 1000000 //10

void fileWrite(long long count[],int nMax)
{
  FILE *fp=fopen("q1a.data","w");
  char names[11][7]={"zero","one","two","three","four","five","six","seven","eight","nine","ten"};

  for(int i=1;i<=nMax;i++)
  {
    printf("%s %lld\n",&names[i][0],count[i]);
    fprintf(fp,"%s %lld\n",&names[i][0],count[i]);
  }
  fclose(fp);
}

void RandomNumberGenerator(const int nMax, const int  nNumOfNumsToGenerate)
{
  int nRandonNumber = 0;
  long long count[7];
  for (int i=1;i<=nMax;i++)
    count[i]=0;
  for (int i = 0; i < nNumOfNumsToGenerate; i++)
  {
    nRandonNumber = rand()%(nMax) + 1;
    //printf("%d ", nRandonNumber);
    count[nRandonNumber]+=1;
  }
  fileWrite(count,nMax);
}



void main()
{
  srand(time(NULL));
  RandomNumberGenerator(6,NumOfTerms);
  system("gnuplot gnucode.txt");
}

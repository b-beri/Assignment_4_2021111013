#include <time.h>
#include <stdlib.h>
#include <stdio.h>

# define NumOfTerms 1000000 //10

void fileWrite(long long count[],int nMax)
{
  FILE *fp=fopen("q2.data","w");
  char names[13][3]={"0","1","2","3","4","5","6","7","8","9","10","11","12"};

  for(int i=2;i<=nMax;i++)
  {
    printf("%s %lld\n",&names[i][0],count[i]);
    fprintf(fp,"%s %lld\n",&names[i][0],count[i]);
  }
  fclose(fp);
}

void RandomNumberGenerator(const int nMax, const int  nNumOfNumsToGenerate)
{
  int nRandonNumber1 = 0,nRandonNumber2 = 0;
  long long count[13];
  for (int i=1;i<=nMax*2;i++)
    count[i]=0;
  for (int i = 0; i < nNumOfNumsToGenerate; i++)
  {
    nRandonNumber1 = rand()%(nMax) + 1;
    nRandonNumber2 = rand()%(nMax) + 1;
    int nRandonNumber = nRandonNumber1 + nRandonNumber2;
    //printf("%d ", nRandonNumber);
    count[nRandonNumber]+=1;
  }
  fileWrite(count,12);
}



void main()
{
  srand(time(NULL));
  RandomNumberGenerator(6,NumOfTerms);
  system("gnuplot gnucode.txt");
}
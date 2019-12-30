#include "Population.h"

int main()
{
  int i;
  Population *pop;

  srand((unsigned int)time(NULL));

  pop = new Population("sampledata.csv");
  for(i = 1; i <= TIME_MAX; i++){
    pop->move();
    printf("時刻%d: 光の最高強度%f\n", i, pop->bestInt);
  }
  pop->printResult();
  delete pop;

  return 0;
}

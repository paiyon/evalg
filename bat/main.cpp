#include "Population.h"

int main()
{
  int t;
  Population *pop;

  srand((unsigned int)time(NULL));

  pop = new Population("sampledata.csv");
  for(t = 1; t <= TIME_MAX; t++) {
    pop->move(t);
    printf("時刻%d: 最良評価値%f\n", t, pop->bestValue);
  }
  pop->printResult();
  delete pop;

  return 0;
}

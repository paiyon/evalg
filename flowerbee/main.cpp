#include "FlowerSet.h"
#include <stdio.h>

int main()
{
  int i;
  FlowerSet *fSet;

  fSet = new FlowerSet("sampledata.csv");
  for(i = 1; i <= REPEAT_NUM; i++){
    fSet->employedBeePhase();
    fSet->onlookerBeePhase();
    fSet->scoutBeePhase();
    fSet->saveBestPos();
    printf("%d回目：最良評価値%f\n", i , fSet->bestValue);
  }
  fSet->printResult();
  delete fSet;

  return 0;
}

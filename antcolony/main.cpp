#include "Colony.h"

int main()
{
  int i;
  Colony *colony;

  srand((unsigned int)time(NULL));

  colony = new Colony("sampledata.csv");

  for(i = 1; i <= REPEAT_NUM; i++){
    colony->selectRoute();
    colony->renewPheromone();
  }
  colony->printPheromone();
  delete colony;

  return 0;
}

#include "HarmonyMemory.h"

int main()
{
  int i;
  HarmonyMemory *hm;

  srand((unsigned int)time(NULL));

  hm = new HarmonyMemory("sampledata.csv");
  for(i = 1; i <= REPEAT_NUM; i++) {
    hm->update();
    printf("%d回目:最良評価値%f\n", i, hm->harmony[hm->best]->value);
  }
  hm->printResult();
  delete hm;

  return 0;
}

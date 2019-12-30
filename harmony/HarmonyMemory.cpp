#include "HarmonyMemory.h"

HarmonyMemory::HarmonyMemory(char *fileName)
{
  int i;

  dataset = new Dataset(fileName);
  harmony = new Harmony* [HM_SIZE];
  best = 0;
  worst = 0;
  for(i = 0; i < HM_SIZE; i++) {
    harmony[i] = new Harmony(this);
    if(harmony[best]->value > harmony[i]->value) {
      best = i;
    }
    if(harmony[worst]->value < harmony[i]->value) {
      worst = i;
    }
  }
  newHarmony = new Harmony(this);
}

HarmonyMemory::~HarmonyMemory()
{
  int i;
  for(i = 0; i < HM_SIZE; i++) {
    delete harmony[i];
  }
  delete [] harmony;
  delete newHarmony;
  delete dataset;
}

void HarmonyMemory::update()
{
  int i;
  Harmony *tmp;

  newHarmony->renew();
  // 最悪ハーモニーより評価が良ければ、確実に更新が発生する
  if(harmony[worst]->value > newHarmony->value) {
    tmp = newHarmony;
    newHarmony = harmony[worst];
    harmony[worst] = tmp;

    // 最良ハーモニーの添え字を更新する
    if(harmony[best]->value > harmony[worst]->value) {
      best = worst;
    }

    // 最悪ハーモニーの添え字を更新する
    worst = 0;
    for(i = 1; i < HM_SIZE; i++) {
      if(harmony[worst]->value < harmony[i]->value){
        worst = i;
      }
    }
  }
}

void HarmonyMemory::printResult()
{
  dataset->setCoef(harmony[best]->chord);
  dataset->printEquation();
}


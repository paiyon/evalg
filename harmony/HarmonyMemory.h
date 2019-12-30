#pragma once
#include "Harmony.h"
class Harmony;

class HarmonyMemory
{
public:
  HarmonyMemory(char *fileName);
  ~HarmonyMemory();
  void update();      //  ハーモニーメモリーを更新する
  void printResult();

  Dataset *dataset;
  Harmony **harmony;  //  現在のハーモニーの集合メンバ
  int best;           //  最良ハーモニーの添え字

private:
  Harmony *newHarmony;//  新しいハーモニー
  int worst;          //  最悪ハーモニーの添え字
};

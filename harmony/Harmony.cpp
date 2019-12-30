#include "Harmony.h"

Harmony::Harmony(HarmonyMemory *argHM)
{
  int i;

  hm = argHM;
  chord = new double [hm->dataset->exVarNum];
  for(i = 0; i < hm->dataset->exVarNum; i++) {
    chord[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
  }
  evaluate();
}

Harmony::~Harmony()
{
  delete [] chord;
}

void Harmony::renew()
{
  int i, r;
  
  for(i = 0; i < hm->dataset->exVarNum; i++) {
    // 既存のハーモニーを選ぶか？
    if(RAND_01 < R_A) {
      r = rand() % HM_SIZE;
      // 選択した和音を変更しつつ取り入れるか？
      if(RAND_01 < R_P) {
        chord[i] = hm->harmony[r]->chord[i]
                  + BANDWIDTH * (rand() / (RAND_MAX / 2.0) - 1);
      } else {
        // 和音を複製する
        chord[i] = hm->harmony[r]->chord[i];
      }
    } else {
      // 新しい和音を生成
      chord[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
    }
  }
  evaluate();
}

void Harmony::evaluate()
{
  int i, j;
  double diff;

  value = 0.0;
  for(i = 0; i < hm->dataset->dataNum; i++) {
    diff = hm->dataset->resSData[i];
    for(j = 0; j < hm->dataset->exVarNum; j++) {
      diff -= chord[j] * hm->dataset->exSData[i][j];
    }
    value += pow(diff, 2.0);
  }
}

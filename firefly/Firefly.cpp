#include "Firefly.h"

Firefly::Firefly(Population *argPop)
{
  int i;

  pop = argPop;
  pos = new double[pop->dataset->exVarNum];
  for(i = 0; i < pop->dataset->exVarNum; i++) {
    pos[i] = COEF_MIN + (COEF_MAX - COEF_MIN) * RAND_01;
  }
  evaluate();
}

Firefly::~Firefly()
{
  delete [] pos;
}

void Firefly::move(Firefly *base)
{
  int i;
  double dis;

  if(intensity > base->intensity){
    //距離を算出する
    dis = 0.0;
    for(i = 0; i < pop->dataset->exVarNum; i++){
      dis += pow(base->pos[i] - pos[i], 2);
    }
    //dis = sqrt(dis);
  

    // 移動先を決定する
    for(i = 0; i < pop->dataset->exVarNum; i++) {
      pos[i] = pos[i]
            + ATTRACT * exp(-ABSORB * dis) * (base->pos[i] - pos[i])
            + RANDOMIZE * (RAND_01 - 0.5);
    }
    evaluate();
  }
}

void Firefly::evaluate()
{
  int i, j;
  double diff;

  intensity = 0.0;
  for(i = 0; i < pop->dataset->dataNum; i++) {
    diff = pop->dataset->resSData[i];
    for(j = 0; j < pop->dataset->exVarNum; j++) {
      diff -= pos[j] * pop->dataset->exSData[i][j];
    }
    intensity += pow(diff, 2.0);
  }
}

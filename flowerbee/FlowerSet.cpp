#include "FlowerSet.h"

FlowerSet::FlowerSet(char *fileName)
{
  int i, best;

  dataset = new Dataset(fileName);
  flower = new Flower* [EBEE_NUM];
  best = 0;
  
  for(i = 0; i < EBEE_NUM; i++){
    flower[i] = new Flower(this);
    if(flower[best]->value > flower[i]->value){
      best = i;
    }
  }
  bestPos = new double [dataset->exVarNum];
  for(i = 0; i < dataset->exVarNum; i++){
    bestPos[i] = flower[best]->pos[i];
  }
  bestValue = flower[best]->value;
  newFlower = new Flower(this);
  trValue = new double [EBEE_NUM];
}

FlowerSet::~FlowerSet()
{
  int i;

  for(i = 0; i < EBEE_NUM; i++){
    delete flower[i];
  }
  delete [] flower;
  delete [] bestPos;
  delete newFlower;
  delete [] trValue;
  delete dataset;
}

void FlowerSet::employedBeePhase()
{
  int i;
  Flower *tmp;

  for(i = 0; i < EBEE_NUM; i++){
    newFlower->change(i);
    if(flower[i]->value > newFlower->value){
      tmp = newFlower;
      newFlower = flower[i];
      flower[i] = tmp;
    }
    flower[i]->visitNum++;
  }
}

void FlowerSet::onlookerBeePhase()
{
  int i, j;
  Flower *tmp;
  double max, min, denom, prob, r;

  for(j = 0; j < OBEE_NUM; j++){
    //convert value(4.6)
    max = DBL_MIN;
    min = DBL_MAX;
    for(i = 0; i < EBEE_NUM; i++){
      if(max < flower[i]->value){
        max = flower[i]->value;
      }
      if(min > flower[i]->value){
        min = flower[i]->value;
      }
    }
    denom = 0.0;
    for(i = 0; i < EBEE_NUM; i++){
      trValue[i] = (max - flower[i]->value) / (max - min);
      denom += trValue[i];
    }

    //収穫バチを選択する
    r = RAND_01;
    for(i = 0; i < EBEE_NUM - 1; i++){
      prob = trValue[i] / denom;
      if(r <= prob){
        break;
      }
      r -= prob;
    }

    //収穫バチフェーズと同様の処理
    newFlower->change(i);
    if(flower[i]->value > newFlower->value){
      tmp = newFlower;
      newFlower = flower[i];
      flower[i] = tmp;
    }
    flower[i]->visitNum++;
  }
}

// 偵察バチ
void FlowerSet::scoutBeePhase()
{
  int i;

  for(i = 0; i < EBEE_NUM; i++){
    if(VISIT_MAX <= flower[i]->visitNum){
      flower[i]->renew();
    }
  }
}

// 最良食料源を記録
void FlowerSet::saveBestPos()
{
  int i, best;
  
  best = -1;
  for(i = 0; i < EBEE_NUM; i++) {
    if(bestValue > flower[i]->value){
      best = i;
    }
  }
  if(best != -1){
    for(i = 0; i < dataset->exVarNum; i++){
      bestPos[i] = flower[best]->pos[i];
    }
    bestValue = flower[best]->value;
  }
}

// 結果を表示する
void FlowerSet::printResult()
{
  dataset->setCoef(bestPos);
  dataset->printEquation();
}


#include "Population.h"

Population::Population(char *fileName)
{
  int i, best;

  dataset = new Dataset(fileName);
  firefly = new Firefly* [POP_SIZE];
  best = 0;
  for(i = 0; i < POP_SIZE; i++) {
    firefly[i] = new Firefly(this);
    //intensityが小さいほど良い
    if(firefly[best]->intensity > firefly[i]->intensity) {
        best = i;
    }
  }
  bestPos = new double [dataset->exVarNum];
  
  for(i = 0; i < dataset->exVarNum; i++) {
    bestPos[i] = firefly[best]->pos[i];
  }
  bestInt = firefly[best]->intensity;
}

Population::~Population()
{
  int i;

  for(i = 0; i < POP_SIZE; i++) {
    delete firefly[i];
  }
  delete [] firefly;
  delete [] bestPos;
  delete dataset;
}

void Population::move()
{
  int i, j, k;

  for(i = 0; i < POP_SIZE; i++) {
    for(j = 0; j < POP_SIZE; j++) {
      //ホタルを移動する
      firefly[i]->move(firefly[j]);
      if(bestInt > firefly[i]->intensity) {
        for(k = 0; k < dataset->exVarNum; k++) {
          bestPos[k] = firefly[i]->pos[k];
        }
        bestInt = firefly[i]->intensity;
      }
    }
  }
}

void Population::printResult()
{
  dataset->setCoef(bestPos);
  dataset->printEquation();
}


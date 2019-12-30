#include "Population.h"

Population::Population(char *fileName)
{
  int i;

  dataset = new Dataset(fileName);
  bat = new Bat* [POP_SIZE];
  for(i = 0; i < POP_SIZE; i++) {
    bat[i] = new Bat(this);
  }
  sort(0, POP_SIZE - 1);
  bestPos = new double [dataset->exVarNum];
  for(i = 0; i < dataset->exVarNum; i++) {
    bestPos[i] = bat[0]->pos[i];
  }
  bestValue = bat[0]->value;
}

Population::~Population()
{
  int i;

  for(i = 0; i < POP_SIZE; i++) {
    delete bat[i];
  }
  delete [] bat;
  delete [] bestPos;
  delete dataset;
}

//t : time
void Population::move(int t)
{
  int i;

  for(i = 0; i < POP_SIZE; i++) {
    bat[i]->move(t);
  }

  // コウモリを良い順に並び変える
  sort(0, POP_SIZE - 1);

  // 最良コウモリを記録する
  if(bat[0]->value < bestValue) {
    for(i = 0; i < dataset->exVarNum; i++) {
      bestPos[i] = bat[0]->pos[i];
    }
    bestValue = bat[0]->value;
  }
}

// sort bat[lb]~bat[ub]
void Population::sort(int lb, int ub)
{
  int i, j, k;
  double pivot;
  Bat *tmp;

  if(lb < ub) {
    k = (lb + ub) / 2;
    pivot = bat[k]->value;
    i = lb;
    j = ub;
    do {
      while(bat[i]->value < pivot) {
        i++;
      }
      while(bat[j]->value > pivot) {
        j--;
      }
      if(i <= j) {
        tmp = bat[i];
        bat[i] = bat[j];
        bat[j] = tmp;
        i++;
        j--;
      }
    } while(i <= j);
    sort(lb , j);
    sort(i, ub);
  }
}

void Population::printResult()
{
  dataset->setCoef(bestPos);
  dataset->printEquation();
}


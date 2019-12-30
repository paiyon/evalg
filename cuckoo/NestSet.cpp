#include "NestSet.h"

NestSet::NestSet(char *fileName)
{
  int i;

  dataset = new Dataset(fileName);
  nest = new Nest* [SET_SIZE];
  for(i = 0; i < SET_SIZE; i++) {
    nest[i] = new Nest(this);
  }
  sort(0, SET_SIZE - 1);
}

NestSet::~NestSet()
{
  int i;

  for(i = 0; i < SET_SIZE; i++) {
    delete nest[i];
  }
  delete [] nest;
  delete dataset;
}

void NestSet::alternate()
{
  int i, r1, r2;

  // 新しい卵を托卵する
  r1 = rand() % SET_SIZE;
  r2 = (r1 + (rand() % (SET_SIZE - 1) + 1)) % SET_SIZE;
  nest[r2]->replace(nest[r1]);

  // 悪い巣を放棄する
  for(i = (int)(SET_SIZE * (1 - ABA_RATE)); i < SET_SIZE; i++) {
    nest[i]->abandon();
  }

  // 巣を良い順に並べる
  sort(0, SET_SIZE - 1);
}

//Quick Sort
//nest[lb]-nest[ub]
void NestSet::sort(int lb, int ub)
{
  int i, j, k;
  double pivot;
  Nest *tmp;

  if(lb < ub) {
    k = (lb + ub) / 2;
    pivot = nest[k]->value;
    i = lb;
    j = ub;
    do {
      while(nest[i]->value < pivot){
        i++;
      }
      while(nest[j]->value > pivot){
        j--;
      }
      if(i <= j) {
        tmp = nest[i];
        nest[i] = nest[j];
        nest[j] = tmp;
        i++;
        j--;
      }
    } while(i <= j);
    sort(lb, j);
    sort(i, ub);
  }
}

void NestSet::printResult()
{
  dataset->setCoef(nest[0]->egg);
  dataset->printEquation();
}

#pragma once
#include "Bat.h"
class Bat;

class Population
{
public:
  Population(char *fileName);
  ~Population();
  void move(int t); // コウモリを移動する
  void printResult();

  Dataset *dataset;
  Bat **bat;        // コウモリ群のメンバ
  double *bestPos;
  double bestValue;

private:
  void sort(int lb, int ub);  // コウモリを良い順に並べ替える

};

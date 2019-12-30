#pragma once
#include "Firefly.h"
class Firefly;

class Population
{
public:
  Population(char *fileName);
  ~Population();
  void move();
  void printResult();

  Dataset *dataset;
  Firefly **firefly;
  double *bestPos;    // 最も明るいホタルの位置
  double bestInt;     // 最も明るいホタルの強度
};

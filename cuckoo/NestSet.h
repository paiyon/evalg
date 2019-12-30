#pragma once
#include "Nest.h"
class Nest;

class NestSet
{
public:
  NestSet(char *fileName);
  ~NestSet();
  void alternate();     // 世代交代
  void printResult();

  Dataset *dataset;
  Nest **nest;

private:
  void sort(int lb, int ub);
};

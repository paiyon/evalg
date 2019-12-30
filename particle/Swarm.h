#pragma once
#include "Particle.h"
class Particle;

class Swarm
{
public:
  Swarm(char *fileName);
  ~Swarm();
  void move();          // move particle
  void printResult();

  Dataset *dataset;
  Particle **particle;
  double *gBestPos;     // グローバルベストの位置
  double gBestValue;    // グローバルベストの評価値
};

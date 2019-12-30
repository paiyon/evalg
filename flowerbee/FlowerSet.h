#pragma once
#include "Flower.h"
class Flower;

class FlowerSet
{
public:
  FlowerSet(char *fileName);
  ~FlowerSet();
  void employedBeePhase(); //emplyoed bee phase
  void onlookerBeePhase();//onlooker bee phase
  void scoutBeePhase();//scout bee phase
  void saveBestPos();
  void printResult();

  Dataset *dataset;
  Flower **flower;
  double *bestPos;
  double bestValue;

private:
  Flower *newFlower;
  double *trValue;

};

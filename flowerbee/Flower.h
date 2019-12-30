#pragma once
#include "Dataset.h"
#include "FlowerSet.h"
class FlowerSet;

// Define Constants
#define REPEAT_NUM  1000
#define EBEE_NUM    100 //The number of employed bees
#define OBEE_NUM    10  //The number of onlooker bees
#define VISIT_MAX   10
#define COEF_MIN    -1 // min of standardised partial regression coefficient
#define COEF_MAX     1 // max of standardised partial regression coefficient

#define RAND_01 ((double)rand() / RAND_MAX)

class Flower
{
public:
  Flower(FlowerSet *argFSet);
  ~Flower();
  void change(int base); // change to a near flower
  void renew();

  FlowerSet *fSet; // belonging flowerset
  double *pos;
  double value;
  int visitNum;

private:
  void evaluate();  // calculate value

};

#pragma once
#include "Field.h"
#include "Colony.h"
class Colony;

//Define constants
#define REPEAT_NUM   1000
#define ANT_NUM     100
#define PHERO_Q     10    //一回の巡回で分泌するフェロモン量
#define EVA_R       0.05  //Probability of the evapolation
#define PHERO_R     0.95  //フェロモンに基づいて経路を選択する確率
#define PHERO_L     1     //フェロモンを考慮する度合
#define HEU_L       1     //Heuristic Infoを考慮する度合

//0-1 rand
#define RAND_01 ((double)rand() / RAND_MAX)

class Ant
{
public:
  Ant(Colony *argColony);
  ~Ant();
  void selectRoute();
  void putPheromone();

  Colony *colony;   //Belonging colony
  int *route;
  double totalDis;  //Total distance

private:
  int *candidate;   //未訪問ノード

};

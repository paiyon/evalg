#include "Individual.h"
#include <stdio.h>

class Population
{
public:
  Population(int selm,int crossm);
  ~Population();
  void alternate(); //世代交代をする
  void printResult();

  Individual **ind; //現世代の個体群のメンバ

private:
  void evaluate();  //個体を評価する
  int select();   //親個体を選択する
  int selectRankingOrder();
  int selectRankingProb();
  int selectRoulette();
  int selectTournament();
  void sort(int lb, int ub);  //個体を良い順に並べる

  Individual **nextInd; //次世代の個体群のメンバ
  
  double trFit[POP_SIZE]; //適応度を変換した値
  double denom;//denominator
  int selectMethod;
};

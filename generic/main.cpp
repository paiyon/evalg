#include "Population.h"
#include <iostream>
#include <stdio.h>

int main()
{
  int i;

  int selm, crossm;
  Population *pop;
  std::cout << "選択メソッド 0:Rank,1:Prob,2:Roulette,3:Tournament >";
  std::cin >> selm;
  if(selm < 0 || selm > 3){
    printf("Error");
    return 0;
  }
  std::cout << "選択交叉 0:Uniform,1:SinglePoint,2:TwoPoint >";
  std::cin >> crossm;
  crossm = 0;
  if(crossm < 0 || crossm > 2){
    printf("Error2");
    return 0;
  }
  srand((unsigned int)time(NULL));

  pop = new Population(selm,crossm);
  for(i = 1; i <= GEN_MAX; i++){
    pop->alternate();
    printf("第%d世代 : 最良適応度%f\n", i, pop->ind[0]->fitness);
  }
  pop->printResult();
  delete pop;

  return 0;
}

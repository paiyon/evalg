#include "Population.h"

// Contrructor
Population::Population(int selm,int crossm)
{
  int i;
  selectMethod = selm;
  ind = new Individual* [POP_SIZE];
  nextInd = new Individual* [POP_SIZE];
  for(i = 0; i < POP_SIZE; i++){
    ind[i] = new Individual(crossm);
    nextInd[i] = new Individual(crossm);
  }
  evaluate();
}

// Destructor
Population::~Population()
{
  int i;
  for(i = 0; i < POP_SIZE; i++){
    delete ind[i];
    delete nextInd[i];
  }
  delete [] ind;
  delete [] nextInd;
}

//Evaluate all the individuals and Sort by their fitness.
void Population::evaluate()
{
  int i;

  for(i = 0; i < POP_SIZE; i++){
    ind[i]->evaluate();
  }
  sort(0, POP_SIZE - 1);
}

// Quick sorting ind[lb] - ind[ub]
// lb : min suffix for the target
// ub : max suffix for the target
void Population::sort(int lb, int ub)
{
  int i, j, k;
  double pivot;//QuickSort pivot
  Individual *tmp;

  if(lb < ub){
    k = (lb + ub) / 2;
    pivot = ind[k]->fitness;
    i = lb;
    j = ub;
    do {
      while(ind[i]->fitness < pivot){
        i++;
      }
      while(ind[j]->fitness > pivot){
        j--;
      }
      if(i <= j){
        tmp = ind[i];
        ind[i] = ind[j];
        ind[j] = tmp;
        i++;
        j--;
      }
    } while(i <= j);
    sort(lb, j);//Recursive sorting for < pivot
    sort(i, ub);//Recursive sorting for > pivot
  }
}

//Alternation of generations
void Population::alternate()
{
  int i, j, p1, p2;
  Individual **tmp;
  
  //For Roulette Select
  denom = 0.0;
  for(i = 0; i < POP_SIZE; i++){
    trFit[i] = (ind[POP_SIZE - 1]->fitness - ind[i]->fitness)
              / (ind[POP_SIZE - 1]->fitness - ind[0]->fitness);
    denom += trFit[i];
  }

  //Elite Save Strategy
  for(i = 0; i < ELITE; i++){
    for(j = 0; j < N; j++){
      nextInd[i]->chrom[j] = ind[i]->chrom[j];
    }
  }
  
  //Select parents and cross over
  for(; i < POP_SIZE; i++){
    p1 = select();
    p2 = select();
    nextInd[i]->crossover(ind[p1], ind[p2]);
  }

  //Mutate
  for(i = 1; i < POP_SIZE; i++){
    nextInd[i]->mutate();
  }

  //Change nextGen -> currentGen
  tmp = ind;
  ind = nextInd;
  nextInd = tmp;

  //Evaluate
  evaluate();
}

int Population::select()
{
  switch(selectMethod){
    case SEL_RANKORDER:
      return selectRankingOrder();
    case SEL_RANKPROB:
      return selectRankingProb();
    case SEL_ROULETTE:
      return selectRoulette();
    case SEL_TOURNAMENT:
      return selectTournament();
  }
}

//Ranking Select
int Population::selectRankingOrder()
{
  int num, denom, r;

  denom = POP_SIZE * (POP_SIZE + 1) / 2;
  r = ((rand() << 16) + (rand() << 1) + (rand() % 2)) % denom + 1;
  for(num = POP_SIZE; 0 < num; num--){
    if(r <= num){
      break;
    }
    r -= num;
  }
  return POP_SIZE - num;
}

int Population::selectRankingProb()
{
  int rank, denom;
  double prob, r;

  denom = POP_SIZE * (POP_SIZE + 1) / 2;
  r = RAND_01;
  for(rank = 1; rank < POP_SIZE; rank++){
    prob = (double)(POP_SIZE - rank + 1) / denom;
    if(r <= prob){
      break;
    }
    r -= prob;
  }
  return rank - 1;
}

int Population::selectRoulette()
{
  int rank;
  double prob, r;
  
  r = RAND_01;
  for(rank = 1; rank < POP_SIZE; rank++){
    prob = trFit[rank - 1] / denom;
    if(r <= prob){
      break;
    }
    r -= prob;
  }
  return rank - 1;
}

int Population::selectTournament()
{
  int i, ret, num, r;
  double bestFit;
  int tmp[N];

  for(i = 0; i < N; i++){
    tmp[i] = 0;
  }
  ret = -1;
  bestFit = DBL_MAX;
  num = 0;
  while(1) {
    r = rand() % N;
    if(tmp[r] == 0){
      tmp[r] = 1;
      if(ind[r]->fitness < bestFit){
        ret = r;
        bestFit = ind[r]->fitness;
      }
      if(++num == TOURNAMENT_SIZE) {
        break;
      }
    }
  }
  return ret;
}

//Show Results
//The best individual is ind[0]
void Population::printResult()
{
  int i;

  printf("集合A: ");
  for(i = 0; i < N; i++){
    if(ind[0]->chrom[i] == 1){
      printf("√%d ", i + 1);
    }
  }

  printf("\n集合B: ");
  for(i = 0; i < N; i++){
    if(ind[0]->chrom[i] == 0){
      printf("√%d ", i + 1);
    }
  }
  printf("\n差: %f\n", ind[0]->fitness);
}



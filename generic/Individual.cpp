#include "Individual.h"

//Constructor
Individual::Individual(int crossm)
{
  int i;
  crossMethod = crossm;
  for(i = 0; i < N; i++){
    chrom[i] = rand() % 2;
  }
  fitness = 0.0;
}

//Destructor
Individual::~Individual()
{
}

//Calculate Fitness
void Individual::evaluate()
{
  int i;

  fitness = 0.0;
  for(i = 0; i < N; i++){
    fitness += (chrom[i] * 2 - 1) * sqrt((double)i + 1);
  }
  fitness = fabs(fitness);
}

void Individual::crossover(Individual *p1, Individual *p2)
{
  switch(crossMethod){
    case CROSS_UNIFORM:
      crossover_uniform(p1,p2);
      break;
    case CROSS_ONEPOINT:
      crossover_one_point(p1,p2);
      break;
    case CROSS_TWOPOINT:
      crossover_two_point(p1,p2);
      break;
  }
}

//Single Point Crossover
void Individual::crossover_one_point(Individual *p1, Individual *p2)
{
  int point, i;

  point = rand() % (N - 1);
  for(i = 0; i <= point; i++){
    chrom[i] = p1->chrom[i];
  }
  for(; i < N; i++){
    chrom[i] = p2->chrom[i];
  }
}

//Two Point Crossover
void Individual::crossover_two_point(Individual *p1, Individual *p2)
{
  int point1, point2, tmp, i;
  
  point1 = rand() % (N - 1);
  point2 = (point1 + (rand() % (N - 2) + 1)) % (N - 1); //point2<>point1 and point2 < N
 
  if(point1 > point2){
    tmp = point1;
    point1 = point2;
    point2 = tmp;
  }
  for(i = 0; i <= point1; i++){
    chrom[i] = p1->chrom[i];
  }
  for(; i <= point2; i++){
    chrom[i] = p2->chrom[i];
  }
  for(; i < N; i++){
    chrom[i] = p1->chrom[i];
  }
}

//Uniform Crossover
void Individual::crossover_uniform(Individual *p1, Individual *p2)
{
  int i;

  for(i = 0; i < N; i++){
    if(rand() % 2 == 1){
      chrom[i] = p1->chrom[i];
    } else {
      chrom[i] = p2->chrom[i];
    }
  }
}

//Mutate
void Individual::mutate()
{
  int i;

  for(i = 0; i < N; i++){
    if(RAND_01 < MUTATE_PROB){
      chrom[i]= 1 - chrom[i];
    }
  }
}


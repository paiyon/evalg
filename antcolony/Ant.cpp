#include "Ant.h"

//Constructor
Ant::Ant(Colony *argColony)
{
  colony = argColony;
  route = new int[colony->field->nodeNum];
  candidate = new int[colony->field->nodeNum];
  route[0] = 0;
  candidate[0] = 0;
  totalDis = 0.0;
}

Ant::~Ant()
{
  delete [] route;
  delete [] candidate;
}

void Ant::selectRoute()
{
  int i, j, next, next2;
  double denom, r, prob;

  //Initialize candidates
  for(i = 1; i < colony->field->nodeNum; i++){
    candidate[i] = 1;
  }

  //Select Route
  totalDis = 0.0;
  for(i = 0; i < colony->field->nodeNum - 2; i++){
    //Calculate denominator
    denom = 0.0;
    for(j = 1; j < colony->field->nodeNum; j++){
      if(candidate[j] == 1){
        denom += colony->nume[route[i]][j];
      }
    }
    //Select next node
    next = -1;
    if((denom != 0.0) && (RAND_01 <= PHERO_R)){
      //based on pheromone
      r = RAND_01;
      for(next = 1; next < colony->field->nodeNum; next++){
        if(candidate[next] == 1){
          prob = colony->nume[route[i]][next] / denom;
          if(r <= prob){
            break;
          }
          r -= prob;
        }
      }
      if(next == colony->field->nodeNum){
        next = -1;
      }
    }
    if(next == -1){
      //Random
      next2 = rand() % (colony->field->nodeNum - i - 1);
      for(next = 1; next < colony->field->nodeNum - 1; next++){
        if(candidate[next] == 1){
          if(next2 == 0){
            break;
          } else {
            next2--;
          }
        }
      }
    }
    route[i + 1] = next;
    candidate[next] = 0;
    totalDis += colony->field->distance[route[i]][next];
  }

  //Last 1 node
  for(next = 1; next < colony->field->nodeNum; next++){
    if(candidate[next] == 1){
      break;
    }
  }
  route[colony->field->nodeNum - 1] = next;
  totalDis += colony->field->distance[route[colony->field->nodeNum - 2]][next];

  //Last 1 node -> Start node
  totalDis += colony->field->distance[next][0];
}

void Ant::putPheromone()
{
  int i;
  double p;

  p = PHERO_Q / totalDis;
  for(i = 0; i < colony->field->nodeNum - 1; i++){
    if(route[i] < route[i + 1]){
      colony->field->pheromone[route[i]][route[i + 1]] += p;
    } else {
      colony->field->pheromone[route[i + 1]][route[i]] += p;
    }
  }
  colony->field->pheromone[0][route[colony->field->nodeNum - 1]] += p;
}


#include "Colony.h"
#include <stdio.h>

//Constructor
//fileName: filename of the dataset
Colony::Colony(char *fileName)
{
  int i;

  field = new Field(fileName);
  ant = new Ant* [ANT_NUM];
  for(i = 0; i < ANT_NUM; i++){
    ant[i] = new Ant(this);
  }
  nume = new double* [field->nodeNum];
  for(i = 0; i < field->nodeNum; i++){
    nume[i] = new double [field->nodeNum];
  }
}

//Destructor
Colony::~Colony()
{
  int i;

  for(i = 0; i < ANT_NUM; i++){
    delete ant[i];
  }
  delete [] ant;
  
  for(i = 0; i < field->nodeNum; i++){
    delete [] nume[i];
  }
  delete [] nume;
  delete field;
}

void Colony::selectRoute()
{
  int i, j;

  //Calculate numerator
  for(i = 0; i < field->nodeNum; i++){
    for(j = 1; j < i; j++){
      nume[i][j] = pow(field->pheromone[j][i], PHERO_L)
                  * pow(1 / field->distance[i][j], HEU_L);
    }
    for(j = i + 1; j < field->nodeNum; j++){
      nume[i][j] = pow(field->pheromone[i][j], PHERO_L)
                  * pow(1 / field->distance[i][j], HEU_L);
    }
  }
  
  //Select Route
  for(i = 0; i < ANT_NUM; i++){
    ant[i]->selectRoute();
  }
}

void Colony::renewPheromone()
{
  int i, j;
  //evaporate
  for(i = 0; i < field->nodeNum; i++){
    for(j = i + 1; j < field->nodeNum; j++){
      field->pheromone[i][j] *= 1 - EVA_R;
    }
  }

  //Addition pheromones by ants
  for(i = 0; i < ANT_NUM; i++){
    ant[i]->putPheromone();
  }
}

void Colony::printPheromone()
{
  int i, j;
  for(i = 0; i < field->nodeNum; i++){
    for(j = 0; j < field->nodeNum; j++){
      printf("%8.3f", field->pheromone[i][j]);
    }
    printf("\n");
  }
}


#pragma once
//#include "Field.h"
//class Field;
#include "Ant.h"
class Ant;

class Colony
{
public:
  Colony(char *fileName);
  ~Colony();
  void selectRoute();    // Select route path
  void renewPheromone(); // Update the amount of pheromones
  void printPheromone(); // Print the amount of pheromones

  Field *field;   // Field of feeding behavior
  Ant **ant;      // Member of colony(Ants)
  double **nume;  // Numerator of the selecting path probability
};

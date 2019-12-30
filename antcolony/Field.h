#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

class Field
{
public:
  Field(char *fileName);
  ~Field();

  int nodeNum;
  double **distance;    // The distance between two nodes.
  double **pheromone;   // The quantity of pheromone in a edge.

};

#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

//Define Constants
#define GEN_MAX     1000 // 世代交代数
#define POP_SIZE    1000 // 個体群のサイズ
#define ELITE       1    // エリート保存戦略で残す個体の群
#define MUTATE_PROB 0.01 // Probability of the mutation
#define N           64   // Squared of the max elements of a set

#define RAND_01 ((double)rand() / RAND_MAX)

#define TOURNAMENT_SIZE 30 // size of the tournament

#define SEL_RANKORDER  0
#define SEL_RANKPROB   1
#define SEL_ROULETTE   2
#define SEL_TOURNAMENT 3

#define CROSS_UNIFORM   0
#define CROSS_ONEPOINT  1
#define CROSS_TWOPOINT  2

class Individual
{
  public:
    Individual(int crossm);
    ~Individual();
    void evaluate();//適応度を算出する
    void crossover(Individual *p1, Individual *p2);//交叉による子にする
    void crossover_one_point(Individual *p1, Individual *p2);//一点交叉
    void crossover_two_point(Individual *p1, Individual *p2);//二点交叉
    void crossover_uniform(Individual *p1, Individual *p2);//一様交叉
    
    void mutate();//突然変異！

    int chrom[N];//染色体
    int crossMethod;
    double fitness;//適応度
};

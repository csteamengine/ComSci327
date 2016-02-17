#ifndef CHARACTER_H
#define CHARACTER_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binheap.h"

typedef struct Point{
  int dist;
  int x_pos;
  int y_pos;
  int visited;
}Point_t;

typedef struct Character{
  char symbol;
  char color[10];
  int x_pos;
  int y_pos;
}Character_t;
int i;
int j;
Point_t NTDist[21][80];
Point_t TDist[21][80];
binheap_node_t *nodes[21][80];
int createPlayer();
int32_t compare(const void *key, const void *with);
int NTPathFind();
int TPathFind();
void printDistanceMaps();
char convertInt(int i);
void moveCharacter();
void createMonsters(int numMonsters);
int dist(Point_t a, Point_t b);

#endif

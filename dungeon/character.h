#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>



typedef struct Point{
  int dist;
  int x_pos;
  int y_pos;
}Point_t;
Point_t NTDist[21][80];
Point_t TDist[21][80];
int createPlayer();
int32_t compare(const void *key, const void *with);
int NTPathFind();
int TPathFind();
void printDistanceMaps();
char convertInt(int i);
void moveCharacter();
#endif

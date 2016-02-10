#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungeonGen.h"
#include "binheap.h"


Tile_t player;
typedef struct Point{
  int dist;
  int x_pos;
  int y_pos;
  int visited;
}Point_t;
Point_t NTDist[21][80];
Point_t TDist[21][80];
void printGrid(int givenGrid[21][80]);
char convertInt(int i);

int createPlayer(){
  int room = rand()%roomSize;
  int rHeight = roomP[room].y_size;
  int rWidth = roomP[room].x_size;
  int rXPos = roomP[room].x_pos;
  int rYPos = roomP[room].y_pos;
  player.symbol = '@';
  player.x_pos = rXPos + (rand()%rWidth);
  player.y_pos = rYPos + (rand()%rHeight);
  player.locked = 1;
  grid[player.y_pos][player.x_pos] = player;
  return 0;
}

int32_t compare(const void *keyG,const void *withG)
{
  return ((Point_t*)keyG)->dist - ((Point_t *)withG)->dist;
}

int NTPathFind(){
  int i;
  int j;
  binheap_t h;
  Point_t pArr[1680];
  binheap_init(&h,compare,NULL);
  printf("%d:%d\n",player.x_pos,player.y_pos);
  for(i= 0;i<21;i++){
    for(j=0;j<80;j++){
      if(i == player.y_pos && j == player.x_pos){
	pArr[i*j].dist= 0;
	pArr[i*j].x_pos = j;
	pArr[i*j].y_pos = i;
	pArr[i*j].visited = 1;
      }else{
	pArr[i*j].dist = 1;
	pArr[i*j].x_pos = j;
	pArr[i*j].y_pos = i;
	pArr[i*j].visited =0;
      }
      binheap_insert(&h,(pArr+(i*j)));
    }
  }
  for(i = 0;i<21;i++){
    for(j = 0;j<80;j++){
      Point_t *point = ((Point_t*)binheap_remove_min(&h));
      if(point->dist == 0){
	printf("\n\n");
      }
      printf("%d",point->dist);
    }
    printf("\n");
  }
  return 0;

}
int TPathFind(){
  printf("Will print out the Tunneling matrix of distances\n");
  return 0;
}
void Printgrid(int givenGrid[21][80]){
  int i;
  int j;
  
  for(i=0;i<21;i++){
    for(j=0;j<80;j++){
      printf("%c",convertInt(givenGrid[i][j]));
    }
    printf("\n");
  }
  
}
char convertInt(int i){
  char temp;
  int j = i;
  if(i<10){
    j+=48;
  }else if(i<36){
    j+=87;
  }else if(i<62){
    j-=36;
    j+=65;
  }else{
    j = 32;
  }
  temp = j;
  return temp;
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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
int dist(Point_t a, Point_t b);
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
  int counter =0;
  binheap_init(&h,compare,NULL);
  /*Fills the binheap with all of the grid items*/
  for(i= 0;i<21;i++){
    for(j=0;j<80;j++){
      if(i == player.y_pos && j == player.x_pos){
	pArr[counter].dist= 0;
	pArr[counter].x_pos = j;
	pArr[counter].y_pos = i;
	pArr[counter].visited = 1;
      }else{
	pArr[counter].dist = 255;
	pArr[counter].x_pos = j;
	pArr[counter].y_pos = i;
	pArr[counter].visited =0;
      }
      binheap_insert(&h,(pArr+counter));
      counter++;
    }
  }
  
  /*Simply for testing purposes. It was to make sure the binheap had all the correct values in it.*/
  
  /* for(i = 0;i<21;i++){ */
  /*   for(j = 0;j<80;j++){ */
  /*     Point_t *point = ((Point_t*)binheap_remove_min(&h)); */
  /*     if(point->dist == 0){ */
  /* 	printf("\n\n"); */
  /*     } */
  /*     printf("%d",point->dist); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  /*Main Loop for Non-Tunneling Path Finding*/
  while(binheap_peek_min(&h)){
    binheap_remove_min(&h);
    printf("%d\n",((Point_t*)binheap_remove_min(&h))->dist);
    
  }
  Point_t a;
  Point_t b;
  a.x_pos = 5;
  a.y_pos = 15;
  b.x_pos = 11;
  b.y_pos = 30;
  printf("%d\n",dist(a,b));
  return 0;

}
int TPathFind(){
  printf("Will print out the Tunneling matrix of distances\n");
  return 0;
}
int dist(Point_t a, Point_t b){
  double distance; 
  distance = sqrt((a.x_pos - b.x_pos) * (a.x_pos - b.x_pos) + (a.y_pos-b.y_pos) *(a.y_pos-b.y_pos));
  return (int) distance;
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


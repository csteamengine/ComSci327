#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungeonGen.h"
#include "binheap.h"


Tile_t player;
void printGrid();
void printNegGrid();
Tile_t negGrid[21][80];
int createPlayer(){
  int room = rand()%roomSize;
  int rHeight = roomP[room].y_size;
  int rWidth = roomP[room].x_size;
  int rXPos = roomP[room].x_pos;
  int rYPos = roomP[room].y_pos;
  player.symbol = '@';
  player.x_pos = rXPos + (rand()%rWidth);
  player.y_pos = rYPos + (rand()%rHeight);
  grid[player.y_pos][player.x_pos] = player;
  return 0;
}

int32_t compare_int(const void *key, const void *with)
{
  return *(const int32_t *) key - *(const int32_t *) with;
}

int NTPathFind(){
  
  
  binheap_t h;
  int32_t a[15];
  for(int i = 0;i< 15;i++){
    a[i] = rand()%5 +1;
  }
  //binheap_init_from_array(&h,a,sizeof(*a),10,compare_int,NULL);
  binheap_init(&h,compare_int,NULL);
  for(int i = 0;i<15;i++){
    binheap_insert(&h,a+i);
  }
  for(int i = 0;i<15;i++){
    printf("%4d\n",*(int *) h.array[i]->datum);
  }
  //printf("%4d\n",*(int *) binheap_peek_min(&h));
  
  //printf("Will print out the Non-Tunneling matrix of distances\n");

  for(int i = 0;i<21;i++){
    for(int j = 0;j<80;j++){
      if(grid[i][j].locked == 0){
	negGrid[i][j].symbol='.';
      }else{
	negGrid[i][j].symbol = ' ';
      }
    }
  }
  printNegGrid();
  return 0;
  
}
int TPathFind(){
  printf("Will print out the Tunneling matrix of distances\n");
  return 0;
}
void printGrid(){
  int i;
  int j;
  for(i=0;i<21;i++){
    for(j=0;j<80;j++){
      printf("%d",grid[i][j].symbol);
    }
    printf("\n");
  }
  
}
void printNegGrid(){
  int i;
  int j;
  for(i=0;i<21;i++){
    for(j=0;j<80;j++){
      printf("%c",negGrid[i][j].symbol);
    }
    printf("\n");
  }
}


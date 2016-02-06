#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungeonGen.h"
Tile_t player;
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
  printf("%c\n",grid[player.y_pos][player.x_pos].symbol);
  return 0;
}
int NTPathFind(){
  printf("Will print out the Non-Tunneling matrix of distances\n");
  return 0;
}

int TPathFind(){
  printf("Will print out the Tunneling matrix of distances\n");
  return 0;
}

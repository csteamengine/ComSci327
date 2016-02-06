#ifndef DUNGEONGEN_H
#define DUNGEONGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <endian.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct Tile{
  char symbol;
  int locked;
  uint8_t hardness;
  uint8_t x_pos;
  uint8_t y_pos;
}Tile_t;
typedef struct Room{
  uint8_t x_pos;
  uint8_t y_pos;
  uint8_t x_size;
  uint8_t y_size;
}Room_t;
Tile_t grid[21][80];
Room_t *roomP;
int roomSize;
int j;
int l;
int seed;
char *fileName;
int printDungeon();
int fillDungeon();
int addRooms();
int cutCorridor();
int sort();
int loadDungeon();
int saveDungeon();

#endif

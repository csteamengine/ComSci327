#include <stdio.h>
#include <stdlib.h>

typedef struct Tile{
  char symbol;
  int locked;
}Tile_t;
typedef struct Room{
    int x_pos;
    int y_pos;
    int x_size;
    int y_size;
  }Room_t;
Tile_t grid[21][80];
int j;
int l;
void printDungeon();
void fillDungeon();
int main(int argc, char *argv[]){
  int seed;
  if(argc == 1){
   seed = 0;
  }else{
   seed = atoi(argv[1]);
  }
  printf("Seed: %d\n",seed);
  fillDungeon();
  printDungeon();
  return 0;
}
void printDungeon(){
  for(j = 0;j< 21;j++){
    for(l = 0;l<80;l++){
      printf("%c",grid[j][l].symbol);
    }
  }
  printf("Text Line 1\nText Line 2\nText Line 3\n");
}
void fillDungeon(){
   for(j = 0;j< 21;j++){
    for(l = 0;l<80;l++){
      grid[j][l].symbol = '.';
    }
  }
}

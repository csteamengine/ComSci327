#include <stdio.h>
#include <stdlib.h>
 typedef struct Room{
    int x_pos;
    int y_pos;
    int x_size;
    int y_size;
    char symbol;
  }Room_t;
  Room_t grid[21][80];
  Room_t temp;
int main(int argc, char *argv[]){
  int j;
  int l;
  int seed;
  if(argc == 1){
    seed = 0;
     for(j = 0;j< 21;j++){
     for(l = 0;l<80;l++){
       grid[j][l].symbol = '.';
       printf("%c",grid[j][l].symbol);
     }
   }
  }else{
   seed = atoi(argv[1]);
   for(j = 0;j< 21;j++){
    for(l = 0;l<80;l++){
      grid[j][l].symbol = '.';
      printf("%c",grid[j][l].symbol);
    }
   }
  }
  printf("%d\n",seed);
  return 0;
}

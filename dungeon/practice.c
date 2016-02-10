#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void printGrid();
typedef struct charGrid{
  char symbol;
}charGrid_t;
charGrid_t grid[40][40];
int main(int argc,char *argv[]){
  int i;
  int j;
  int centerx=20;
  int centery=20;
  int x;
  int y;
  for(i =0;i<62;i++){
    j = i;
    if(i<10){
      j+=48;
    }else if(i<36){
      j+=87;
    }else if(i<62){\
      j-=36;
      j+= 65;
    }
    char temp = j;
    printf("%c\n",j);
  }
  return 0;
}
void printGrid(){
  int i;
  int j;
  for(i = 0;i<40;i++){
    for(j =0;j<40;j++){
      printf("%s",'1');
    }
    printf("\n");
  }
}

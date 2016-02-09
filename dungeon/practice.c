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
  char distance[61] = {'1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k',
		       'l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E',
		       'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  printf(distance);
  
  // for(i=0;i<40;i++){
    //for(j=0;j<40;j++){
      //grid[i][j].symbol = '.';   
      //}
    //}
  //printGrid();
  //grid[20][20].symbol = '0';
  //for(i=1;i<10;i++){
  //for(y = centery-i;y<centery+i;y++){
  //  grid[y][centerx-i].symbol = (distance+i);
  //}
  // for(y = centery-i;y<centery+i;y++){
  //   grid[y][centerx+i].symbol = (distance+i);
  // }
  //}
  //for(i=1;i<10;i++){
  // for(x = centerx-i;x<centerx+i;x++){
  //   grid[centery-i][x].symbol = (distance+i);
  // }
  // for(x = centerx-i;x<centerx+i;x++){
  //   grid[centery+i][x].symbol = (distance+i);
  // }
  //}
  //printGrid();
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

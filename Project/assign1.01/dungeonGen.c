#include <stdio.h>

int main(int argc, char *argv[]){
  int i;
  int j;
  char grid[21][80];
  for(i = 0;i<21;i++){
    for(j = 0; j< 80;j++){
      if(j > 30 && j < 60){
	grid[i][j] = '.';
      }else{
	grid[i][j] = '#';
      }
    }
  }
  for(i = 0; i<21; i++){
    for(j = 0;j<80;j++){
      printf("%c",grid[i][j]);
    }
    printf("\n");
  }
  return 0;
}

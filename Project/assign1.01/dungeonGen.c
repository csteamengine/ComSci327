#include <stdio.h>

int main(int argc, char *argv[]){
  int i;
  int j;
  char rooms[10];
  for(i = 0;i< 10;i++){
    rooms[i] ='.';
  }
  for(i = 0;i<21;i++){
    for(j = 0; j< 80;j++){
      printf(".");
    }
    printf("\n");
  }
  return 0;
}

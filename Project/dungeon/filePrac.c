#include <stdio.h>
#include <stdlib.h>
#include <endian.h>
#include <string.h>
#include <stdint.h>

int grid[21][80];
void createfileContents();
void printGrid();
int main(int argc, char *argv[]){
  int i;
  int j;
  int empty =0;
  uint8_t x_pos;
  uint8_t y_pos;
  uint8_t prevX;
  uint8_t prevY;
  uint8_t x_size;
  uint8_t y_size;
  uint8_t temp;
  char RLG327[7];
  uint32_t fileSize;
  uint32_t fileVersion;
  FILE *dungeonFile;
  dungeonFile = fopen(strcat(getenv("HOME"),"/.rlg327/smile.rlg327"),"r");
  fread(RLG327, 1, 6, dungeonFile); //file type marker
  fread(&fileVersion,sizeof(fileVersion),1,dungeonFile); //File Version
  fread(&fileSize,sizeof(fileSize),1,dungeonFile);  //File Size
  //  fileSize = htobe32(fileSize);  //FileSize conversion
  for(i = 1;i< 20;i++){
    for(j=1;j<79;j++){
      fread(&temp,sizeof(temp),1,dungeonFile);  //Cell hardness,not border
    }
  }
  while(1){
    prevX = x_pos;
    prevY = y_pos;
    fread(&x_pos,sizeof(x_pos),1,dungeonFile);
    fread(&y_pos,sizeof(y_pos),1,dungeonFile);
    fread(&x_size,sizeof(x_size),1,dungeonFile);
    fread(&y_size,sizeof(y_size),1,dungeonFile);
    if(x_pos == prevX && y_pos == prevY){
      break;
    }
    printf("%d : %d : %d : %d\n",x_pos,y_pos,x_size,y_size);
  }
  return 0;
}
void createFileContents(){
  
}
void printGrid(){
  int i;
  int j;
  for(i = 0;i<21;i++){
    for(j = 0;j<80;j++){
      printf("%d",grid[i][j]);
    }
    printf("\n");
  }
  for(i = 0;i< 3;i++){
    printf("Text Line %d\n",i);
  }
}

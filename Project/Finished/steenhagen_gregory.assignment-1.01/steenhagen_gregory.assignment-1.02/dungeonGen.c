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
int main(int argc, char *argv[]){ 
  int SaveBool = 0;   /* False == 0 */
  int LoadBool = 0;   /* False == 0 */
  char *save = "--save";
  char *load = "--load";
  if(argc == 1){
    seed = time(NULL);
    srand(seed);
  }else if(argc == 2){
    char *argv1 = argv [1];
    if(strcmp(argv1,save) == 0){
      SaveBool =1;
      seed = time(NULL);
      srand(seed);
    }else if(strcmp(argv1,load) == 0){
      fprintf(stderr,"Incorrect Command Line Parameters\n");
    }else{
      seed = atoi(argv[1]);
      srand(seed);
    }
  }else if(argc == 3){
    char *argv1 = argv [1];
    char *argv2 = argv [2];
    if(argv[1][0] == '-' && argv[2][0] == '-'){
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
      
    }else if(argv[1][0] == '-' && argv[2][0] != '-'){
      if(strcmp(argv1,save) == 0){
	SaveBool =1;
	seed = time(NULL);
	srand(seed);
	fileName = argv2;
      }else if(strcmp(argv1,load) == 0){
	LoadBool = 1;
	fileName = argv2;/*Make filename argv2*/
      }else{
	fprintf(stderr,"Incorrect Command Line Parameters\n");
	return -1;
      }
    }else if(argv[1][0] != '-' && argv[2][0] == '-'){
      if(strcmp(argv2,save) == 0){
	SaveBool =1;
	seed = atoi(argv[1]);
	srand(seed);
      }else{
	fprintf(stderr,"Incorrect Command Line Parameters\n");
	return -1;
      }
    }else{
      fprintf(stderr, "Incorrect Command Line Parameters\n");
      return -1;
    }
  }else if(argc == 4){
    char *argv1 = argv [1];
    char *argv2 = argv [2];
    char *argv3 = argv [3];

    if(strcmp(argv1,save) == 0 && strcmp(argv2,load)==0){
      SaveBool = 1;
      LoadBool = 1;
      fileName = argv3;
    }else if(strcmp(argv1,load) == 0 && strcmp(argv2,save) ==0){
      SaveBool = 1;
      LoadBool =1;
      fileName = argv3;
    }else{
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
    }
  }
  

 
  if(LoadBool == 1){
    fillDungeon();
    loadDungeon();
  }else{
     int random = rand()%3 +5;
     roomP = malloc(random * sizeof(Room_t));
     roomSize = random;
     fillDungeon();
     addRooms();
     cutCorridor();
  }
  if(SaveBool == 1){
    saveDungeon();
  }
  printf("Seed: %d\n",seed);
  printDungeon();
  free(roomP);
  return 0;
}
int loadDungeon(){
  int col;
  int row;
  int numRooms;
  uint8_t x_pos;
  uint8_t y_pos;
  uint8_t x_size;
  uint8_t y_size;
  uint8_t hardness;
  char RLG327[6];
  char *home;
  uint32_t fileSize;
  uint32_t fileVersion;
  FILE *dungeonFile;
  home = malloc(1024 * sizeof(char));
  strcpy(home,getenv("HOME"));
  dungeonFile = fopen(strcat(strcat(home,"/.rlg327/"),fileName),"r");
  fread(RLG327, 1, 6, dungeonFile); //file type marker
  fread(&fileVersion,sizeof(fileVersion),1,dungeonFile); //File Version
  fread(&fileSize,sizeof(fileSize),1,dungeonFile);  //File Size
  fileSize = htobe32(fileSize);  //FileSize conversion
  numRooms = (fileSize-1496)/4;
  roomP = malloc(numRooms * sizeof(Room_t));
  roomSize = numRooms;
  for(l = 1;l< 20;l++){
    for(j=1;j<79;j++){
      fread(&hardness,sizeof(hardness),1,dungeonFile);  //Cell hardness
      grid[l][j].hardness = hardness;
      if(grid[l][j].hardness ==0){
	grid[l][j].symbol = '#';
      }
    }
  }
  for(l = 0;l<roomSize;l++){
    fread(&x_pos,sizeof(x_pos),1,dungeonFile);
    fread(&y_pos,sizeof(y_pos),1,dungeonFile);
    fread(&x_size,sizeof(x_size),1,dungeonFile);
    fread(&y_size,sizeof(y_size),1,dungeonFile);
    (roomP+l)->x_pos = x_pos;
    (roomP+l)->y_pos = y_pos;
    (roomP+l)->x_size = x_size;
    (roomP+l)->y_size = y_size; 
    for(col = 0;col<y_size;col++){
      for(row = 0;row<x_size;row++){
	grid[col+y_pos][row+x_pos].symbol = '.';
      }
    }
  }
  fclose(dungeonFile);
  free(home);
  return 0;
}
int saveDungeon(){
  char fileIdentifier[6] = "RLG327";
  char *home = malloc(1024 * sizeof(char));
  FILE *dungeonFile;
  uint32_t fileSize;
  uint32_t fileVersion = 0;
  strcpy(home,getenv("HOME"));
  dungeonFile = fopen(strcat(strcat(home,"/.rlg327/"),fileName),"w");
  fwrite(&fileIdentifier,sizeof(fileIdentifier),1,dungeonFile);
  //file size = 1496 + roomSize * 4;
  fileVersion = htobe32(fileVersion);
  fwrite(&fileVersion,sizeof(fileVersion),1,dungeonFile);


  fileSize = 1496 + (roomSize*4);
  fileSize = htobe32(fileSize);
  fwrite(&fileSize,sizeof(fileSize),1,dungeonFile);
  for(l = 1;l<20;l++){
    for(j=1;j<79;j++){
      fwrite(&grid[l][j].hardness,sizeof(uint8_t),1,dungeonFile);
    }
  }
  for(l = 0;l<roomSize;l++){
    fwrite(&(roomP+l)->x_pos,sizeof(uint8_t),1,dungeonFile);
    fwrite(&(roomP+l)->y_pos,sizeof(uint8_t),1,dungeonFile);
    fwrite(&(roomP+l)->x_size,sizeof(uint8_t),1,dungeonFile);
    fwrite(&(roomP+l)->y_size,sizeof(uint8_t),1,dungeonFile);
  }
  fclose(dungeonFile);
  free(home);
  return 0;
  
}
int printDungeon(){
  for(j = 0;j< 21;j++){
    for(l = 0;l<80;l++){
      printf("%c",grid[j][l].symbol);
    }
    printf("\n");
  }
  printf("Text Line 1\nText Line 2\nText Line 3\n");
  return 0;
}
int fillDungeon(){
   for(j = 0;j< 80;j++){
    for(l = 0;l<21;l++){
      grid[l][j].symbol = ' ';
      grid[l][j].hardness = rand()%204 + 50;
      if(j == 0 || j== 79){
	grid[l][j].hardness = 255;
	grid[l][j].locked = 1;
      }
      if(l == 0 || l == 20){
	grid[l][j].hardness = 255;
	grid[l][j].locked = 1;
      }
    }
  }
  return 0;
}
int addRooms(){
  uint8_t xCoord;
  uint8_t yCoord;
  uint8_t rHeight;
  uint8_t rWidth;
  int j;
  for(j = 0;j<roomSize;j++){
    if(j == 0){
      rHeight = rand()%7+3;
      rWidth = rand()%7+3;
      xCoord = rand()%69+1;
      yCoord = rand()%10+1;
      for(int i = xCoord;i<xCoord + rWidth;i++){
	for(int k = yCoord; k<yCoord + rHeight;k++){
	  grid[k][i].symbol = '.';
	  grid[k][i].locked = 1;
	  grid[k][i].hardness = 0;
	}
      }
    }else{
      rHeight = rand()%7+3;
      rWidth = rand()%7+3;
      xCoord = rand()%69+1;
      yCoord = rand()%10+1;
      int counter = 0;
      int  avail = 1;
      while(avail==1){
	counter++;
	for(int i = xCoord-1;i<=rWidth + xCoord +1;i++){
	  for(int k = yCoord-1;k<=rHeight + yCoord + 1;k++){
	    if(grid[k][i].locked ==1){
	      avail = 1;
	      xCoord = rand()%69+1;
	      yCoord = rand()%10+1;
	      break;
	    }else{
	      avail = 0;
	    }
	  }
	  if(avail==1){
	    break;
	  }
	}
	if(counter > 1000){
	  rHeight = rand()%7+3;
	  rWidth = rand()%7+3;
	}
      }
      for(int i = xCoord;i<xCoord + rWidth;i++){
	for(int k = yCoord; k<yCoord + rHeight;k++){
	  grid[k][i].symbol = '.';
	  grid[k][i].locked = 1;
	  grid[k][i].hardness = 0;
	}
      }
    }
    (roomP+j)->x_pos = xCoord;
    (roomP+j)->y_pos = yCoord;
    (roomP+j)->x_size = rWidth;
    (roomP+j)->y_size = rHeight;
  }
  return 0;
}
int cutCorridor(){
  sort();
  int counter = 0;
  while(counter < roomSize-1){
    int curX = (roomP+counter)->x_pos + ((roomP+counter)->x_size)/2-1;
    int curY = (roomP+counter)->y_pos + ((roomP+counter)->y_size)/2-1;
    int tarX = (roomP+counter+1)->x_pos+((roomP+counter+1)->x_size)/2-1;
    int tarY = (roomP+counter+1)->y_pos+((roomP+counter+1)->y_size)/2-1;
    if((roomP+counter+1)->x_size == 3){
      tarX = (roomP+counter+1)->x_pos +1;
    }
    if((roomP+counter+1)->y_size == 3){
      tarY = (roomP+counter+1)->y_pos +1;
    }
    while(curX != tarX){
      
      if(curX <= tarX){
	curX++;
	if(grid[curY][curX].locked == 0){
	  grid[curY][curX].symbol = '#';
	  grid[curY][curX].locked = 1;
	  grid[curY][curX].hardness = 0;
	}
	
      }else if(curX >= tarX){
	curX--;
	if(grid[curY][curX].locked == 0){
	  grid[curY][curX].symbol = '#';
	  grid[curY][curX].locked = 1;
	  grid[curY][curX].hardness = 0;
	}
      }
    }
    while(curY != tarY){
      if(curY <= tarY){
	curY++;
	if(grid[curY][curX].locked == 0){
	  grid[curY][curX].symbol = '#';
	  grid[curY][curX].locked = 1;
	  grid[curY][curX].hardness = 0;
	}
      }else if(curY >= tarY){
	curY--;
	if(grid[curY][curX].locked == 0){
	  grid[curY][curX].symbol = '#';
	  grid[curY][curX].locked = 1;
	  grid[curY][curX].hardness = 0;
	}
      }
    }
    counter++;
  }
  return 0;
}
int sort(){
  for(int l = 0;l<roomSize;l++){
    int low= l;
    for(int i = l+1;i<roomSize;i++){
      if((roomP+i)->x_pos<(roomP+low)->x_pos){
	low = i;
      }else if((roomP+i)->x_pos == (roomP+low)->x_pos){
	if((roomP+i)->y_pos < (roomP+low)->y_pos){
	  low = i;
	}
      }
    }
    Room_t temp = *(roomP+l);
    *(roomP+l) = *(roomP+low);
    *(roomP+low) = temp;
  }

  return 0;
}

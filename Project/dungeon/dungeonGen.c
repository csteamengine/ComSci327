#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <endian.h>
#include <string.h>
#include <stdint.h>
  
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
int j;
int l;
int seed;
int printDungeon();
int fillDungeon();
int addRooms(Room_t *roomPoint,int size);
int cutCorridor(Room_t *rPointer,int size);
int sort(Room_t *rPointer, int size);
int loadDungeon(Room_t *roomPoint);
int countRooms();
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
      LoadBool = 1;
    }else{
      seed = atoi(argv[1]);
      srand(seed);
    }
  }else if(argc == 3){
    char *argv1 = argv [1];
    char *argv2 = argv [2];
    if(argv[1][0] == '-' && argv[2][0] == '-'){
      if(strcmp(argv1,save) == 0 && strcmp(argv2,load)==0){
	SaveBool = 1; /*Will load a dungeon from file and then save it again*/
	LoadBool = 1;
      }else if(strcmp(argv1,load)== 0 && strcmp(argv2,save) == 0){
	SaveBool = 1;  /*Will load a dungeon from file and then save it again*/
	LoadBool = 1;
      }else{
	fprintf(stderr,"Incorrect Command Line Parameters\n");
	return -1;
      } 
    }else if(argv[1][0] == '-' && argv[2][0] != '-'){
      if(strcmp(argv1,save) == 0){
	SaveBool =1;
	seed = atoi(argv[2]);
	srand(seed);
      }else if(strcmp(argv1,load) == 0){
	LoadBool = 1;
	/*Make filename argv2*/
      }else{
	fprintf(stderr,"Incorrect Command Line Parameters\n");
	return -1;
      }
    }else if(argv[1][0] != '-' && argv[2][0] == '-'){
      if(strcmp(argv2,save) == 0){
	SaveBool =1;
	seed = atoi(argv[1]);
	srand(seed);
      }else if(strcmp(argv1,load) == 0){
	LoadBool = 1;
	/*Make file name argv1*/
      }else{
	fprintf(stderr,"Incorrect Command Line Parameters\n");
	return -1;
      }
    }else{
      fprintf(stderr, "Incorrect Command Line Parameters\n");
      return -1;
    }
  }else if(argc == 4){
    printf("Load a file %s and save it again\n",argv[3]);
  }

  if(SaveBool == 1){
    printf("Save switch activated\n");
  }
  if(LoadBool == 1){
    Room_t *roomP;
    int numRooms = countRooms();
    roomP = malloc(numRooms * sizeof(Room_t));
    loadDungeon(roomP);
    free(roomP);
    return 0; /*Just for now. Will eventually open a file instead of creating
		new dungeon with 0 as the seed*/
  }else{
     int random = rand()%3 +5;
     Room_t *roomP;
     roomP = malloc(random * sizeof(Room_t));
     fillDungeon();
     addRooms(roomP,random);
     cutCorridor(roomP,random);
     free(roomP);
  }
  printf("Seed: %d\n",seed);
  printDungeon();
  return 0;
}
int countRooms(){
  int i;
  int j;
  uint8_t x_pos;
  uint8_t y_pos;
  uint8_t prevX;
  uint8_t prevY;
  uint8_t x_size;
  uint8_t y_size;
  uint8_t temp;
  int numRooms = 0;
  char RLG327[7];
  uint32_t fileSize;
  uint32_t fileVersion;
  FILE *dungeonFile;
  dungeonFile = fopen(strcat(getenv("HOME"),"/.rlg327/smile.rlg327"),"r");
  fread(RLG327, 1, 6, dungeonFile); //file type marker
  fread(&fileVersion,sizeof(fileVersion),1,dungeonFile); //File Version
  fread(&fileSize,sizeof(fileSize),1,dungeonFile);  //File Size
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
    numRooms++;
  }
  return numRooms;
}
int loadDungeon(Room_t *roomP){
  int i;
  int j;
  int count =0;
  uint8_t x_pos;
  uint8_t y_pos;
  uint8_t prevX;
  uint8_t prevY;
  uint8_t x_size;
  uint8_t y_size;
  uint8_t hardness;
  char RLG327[7];
  uint32_t fileSize;
  uint32_t fileVersion;
  FILE *dungeonFile;
  dungeonFile = fopen(strcat(getenv("HOME"),"/.rlg327/smile.rlg327"),"r");
  fread(RLG327, 1, 6, dungeonFile); //file type marker
  fread(&fileVersion,sizeof(fileVersion),1,dungeonFile); //File Version
  fread(&fileSize,sizeof(fileSize),1,dungeonFile);  //File Size
  fileSize = htobe32(fileSize);  //FileSize conversion
  for(i = 1;i< 20;i++){
    for(j=1;j<79;j++){
      fread(&hardness,sizeof(hardness),1,dungeonFile);  //Cell hardness
      grid[i][j].hardness = hardness;
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
    (roomP+count)->x_pos = x_pos;
    (roomP+count)->y_pos = y_pos;
    (roomP+count)->x_size = x_size;
    (roomP+count)->y_size = y_size;
    for(i = y_pos;i<y_pos+y_size;i++){
      for(j=x_pos;j<x_pos+x_size;j++){
	grid[i][j].symbol = '.';
      }
    }
  }
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
    }
  }
  return 0;
}
int addRooms(Room_t *roomPointer,int size){
  uint8_t xCoord;
  uint8_t yCoord;
  uint8_t rHeight;
  uint8_t rWidth;
  int j;
  for(j = 0;j<size;j++){
    if(j == 0){
      rHeight = rand()%7+3;
      rWidth = rand()%7+3;
      xCoord = rand()%69+1;
      yCoord = rand()%10+1;
      for(int i = xCoord -1;i<xCoord + rWidth +1;i++){
	for(int k = yCoord -1; k<yCoord + rHeight + 1;k++){
	  grid[k][i].symbol = '.';
	  grid[k][i].locked = 1;
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
      for(int i = xCoord;i<=xCoord + rWidth;i++){
	for(int k = yCoord; k<=yCoord + rHeight;k++){
	  grid[k][i].symbol = '.';
	  grid[k][i].locked = 1;
	}
      }
    }
    (roomPointer+j)->x_pos = xCoord;
    (roomPointer+j)->y_pos = yCoord;
    (roomPointer+j)->x_size = rWidth;
    (roomPointer+j)->y_size = rHeight;
  }
  return 0;
}
int cutCorridor(Room_t *rPoint,int size){
  sort(rPoint,size);
  int counter = 0;
  while(counter < size-1){
    int curX = (rPoint+counter)->x_pos + ((rPoint+counter)->x_size)/2-1;
    int curY = (rPoint+counter)->y_pos + ((rPoint+counter)->y_size)/2-1;
    int tarX = (rPoint+counter+1)->x_pos+((rPoint+counter+1)->x_size)/2-1;
    int tarY = (rPoint+counter+1)->y_pos+((rPoint+counter+1)->y_size)/2-1;
    if((rPoint+counter+1)->x_size == 3){
      tarX = (rPoint+counter+1)->x_pos +1;
    }
    if((rPoint+counter+1)->y_size == 3){
      tarY = (rPoint+counter+1)->y_pos +1;
    }
    while(curX != tarX){
      
      if(curX <= tarX){
	curX++;
	if(grid[curY][curX].locked == 0){
	  grid[curY][curX].symbol = '#';
	  grid[curY][curX].locked = 1;
	}
	
      }else if(curX >= tarX){
	curX--;
	if(grid[curY][curX].locked == 0){
	  grid[curY][curX].symbol = '#';
	  grid[curY][curX].locked = 1;
	}
      }
    }
    while(curY != tarY){
      if(curY <= tarY){
	curY++;
	if(grid[curY][curX].locked == 0){
	  grid[curY][curX].symbol = '#';
	  grid[curY][curX].locked = 1;
	}
      }else if(curY >= tarY){
	curY--;
	if(grid[curY][curX].locked == 0){
	  grid[curY][curX].symbol = '#';
	  grid[curY][curX].locked = 1;
	}
      }
    }
    counter++;
  }
  return 0;
}
int sort(Room_t *rPointer, int size){
  for(int l = 0;l<size;l++){
    int low= l;
    for(int i = l+1;i<size;i++){
      if((rPointer+i)->x_pos<(rPointer+low)->x_pos){
	low = i;
      }else if((rPointer+i)->x_pos == (rPointer+low)->x_pos){
	if((rPointer+i)->y_pos < (rPointer+low)->y_pos){
	  low = i;
	}
      }
    }
    Room_t temp = *(rPointer+l);
    *(rPointer+l) = *(rPointer+low);
    *(rPointer+low) = temp;
  }

  return 0;
}

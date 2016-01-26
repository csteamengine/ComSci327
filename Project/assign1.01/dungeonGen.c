#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
int printDungeon();
int fillDungeon();
int addRooms(Room_t *roomPoint,int size);
int cutCorridor(Room_t *rPointer,int size);

int main(int argc, char *argv[]){
  int seed;
  if(argc == 1){
    seed = time(NULL);
    srand(seed);
  }else{
   seed = atoi(argv[1]);
   srand(seed);
  }
  int random = rand()%3 +5;
  Room_t *roomP;
  roomP = malloc(sizeof(*roomP)*random);
  printf("Seed: %d\n",seed);
  printf("Rooms Length: %d\n",random);
  fillDungeon();
  addRooms(roomP,random);
  printf("Rooms Length: %d\n",sizeof(roomP)/sizeof(Room_t));
  printDungeon();
  return 0;
}
int printDungeon(){
  for(j = 0;j< 21;j++){
    for(l = 0;l<80;l++){
      printf("%c",grid[j][l].symbol);
    }
  }
  printf("Text Line 1\nText Line 2\nText Line 3\n");
  return 0;
}
int fillDungeon(){
   for(j = 0;j< 21;j++){
    for(l = 0;l<80;l++){
      grid[j][l].symbol = ' ';
    }
  }
  return 0;
}
int addRooms(Room_t *roomPointer,int size){
  int xCoord;
  int yCoord;
  int rHeight;
  int rWidth;
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
    roomPointer->x_pos = xCoord;
    roomPointer->y_pos = yCoord;
    roomPointer->x_size = rWidth;
    roomPointer->y_size = rHeight;
  }
  return 0;
}
int cutCorridor(Room_t *roomPoint,int size){
  sort(roomPoint,size);
  int counter = 0;
  while(counter < size-1){
    int curX = roomPoint[counter]->x_pos + (roomPoint[counter]->x_size)/2-1;
    int curY = roomPoint[counter]->y_pos + (roomPoint[counter]->y_size)/2-1;
    int tarX = roomPoint[counter+1]->x_pos + (roomPoint[counter+ 1]->x_size)/2-1;
    int tarY = roomPoint[counter+1]->y_pos + (roomPoint[counter+ 1]->y_size)/2-1;
    if(roomPoint[counter+1]->x_size == 3){
      tarX = roomPoint[counter+1]->x_pos +1;
    }
    if(roomPoint[counter+1]->y_size == 3){
      tarY = roomPoint[counter+1]->y_pos +1;
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
      if(rPointer[i]->x_pos<rPointer[low]->x_pos){
	low = i;
      }else if(rPointer[i]->x_pos == rPointer[low]->x_pos){
	if(rPointer[i]->y_pos < rPointer[low]->y_pos){
	  low = i;
	}
      }
    }
    Room_t temp = rPointer[l];
    rPointer[l] = rPointer[low];
    rPointer[low] = temp;
  }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "dungeonGen.h"
#include "binheap.h"


Tile_t player;
typedef struct Point{
  int dist;
  int x_pos;
  int y_pos;
  int visited;
}Point_t;
Point_t NTDist[21][80];
Point_t TDist[21][80];
binheap_node_t *nodes[21][80];
char convertInt(int i);
int dist(Point_t a, Point_t b);
void printDistanceMaps();
int createPlayer(){
  int room = rand()%roomSize;
  int rHeight = roomP[room].y_size;
  int rWidth = roomP[room].x_size;
  int rXPos = roomP[room].x_pos;
  int rYPos = roomP[room].y_pos;
  player.symbol = '@';
  player.x_pos = rXPos + (rand()%rWidth);
  player.y_pos = rYPos + (rand()%rHeight);
  player.locked = 1;
  grid[player.y_pos][player.x_pos] = player;
  return 0;
}

int32_t compare(const void *keyG,const void *withG)
{
  return ((Point_t*)keyG)->dist - ((Point_t *)withG)->dist;
}

int NTPathFind(){
  int i;
  int j;
  binheap_t h;
  binheap_init(&h,compare,NULL);
  /*Fills the binheap with all of the grid items*/
  for(i= 1;i<20;i++){
    for(j=1;j<79;j++){      
       if(i == player.y_pos && j == player.x_pos){
	NTDist[i][j].dist= 0;
	NTDist[i][j].x_pos = j;
	NTDist[i][j].y_pos = i;
	NTDist[i][j].visited = 0;
	}else{
	NTDist[i][j].dist = 255;
	NTDist[i][j].x_pos = j;
        NTDist[i][j].y_pos = i;
	NTDist[i][j].visited =0;
       }
       nodes[i][j] = binheap_insert(&h,&NTDist[i][j]);      
    }
  }
  Point_t *curr;
  while((curr = ((Point_t*)binheap_remove_min(&h)))){
    int x = curr->x_pos;
    int y = curr->y_pos;
    nodes[y][x] = NULL;
    int alt;
    for(i =y-1;i<=y+1;i++){
      for(j = x-1;j<=x+1;j++){
    	if(nodes[i][j] && grid[i][j].hardness == 0){
	  alt = NTDist[y][x].dist + dist(NTDist[y][x],NTDist[i][j]);
    	  if(alt < NTDist[i][j].dist){
    	    NTDist[i][j].dist = alt;
    	    binheap_decrease_key(&h,nodes[i][j]);
    	   }
    	}
      }
    }
  }
  return 0;
}

int32_t compareTunneling(const void *keyG,const void *withG)
{
  int kx = ((Point_t*)keyG)->x_pos;
  int ky = ((Point_t*)keyG)->y_pos;
  int wx = ((Point_t*)withG)->x_pos;
  int wy = ((Point_t*)withG)->y_pos;
  
  return (((Point_t*)keyG)->dist + (grid[ky][kx].hardness/60)) - (((Point_t *)withG)->dist + (grid[wy][wx].hardness/60));
}
int TPathFind(){
    int i;
  int j;
  binheap_t h;
  binheap_init(&h,compareTunneling,NULL);
  /*Fills the binheap with all of the grid items*/
  for(i= 1;i<20;i++){
    for(j=1;j<79;j++){      
       if(i == player.y_pos && j == player.x_pos){
	TDist[i][j].dist= 0;
	TDist[i][j].x_pos = j;
	TDist[i][j].y_pos = i;
	TDist[i][j].visited = 0;
	}else{
	TDist[i][j].dist = 255;
	TDist[i][j].x_pos = j;
        TDist[i][j].y_pos = i;
	TDist[i][j].visited =0;
       }
       nodes[i][j] = binheap_insert(&h,&TDist[i][j]);      
    }
  }
  Point_t *curr;
  while((curr = ((Point_t*)binheap_remove_min(&h)))){
    int x = curr->x_pos;
    int y = curr->y_pos;
    nodes[y][x] = NULL;
    int alt;
    for(i =y-1;i<=y+1;i++){
      for(j = x-1;j<=x+1;j++){
    	if(nodes[i][j]){
	  alt = TDist[y][x].dist + dist(TDist[y][x],TDist[i][j]) + (grid[i][j].hardness/60);
    	  if(alt < TDist[i][j].dist){
    	    TDist[i][j].dist = alt;
    	    binheap_decrease_key(&h,nodes[i][j]);
    	   }
    	}
      }
    }
  }
  return 0;
}
int dist(Point_t a, Point_t b){
  double distance; 
  distance = sqrt((a.x_pos - b.x_pos) * (a.x_pos - b.x_pos) + (a.y_pos-b.y_pos) *(a.y_pos-b.y_pos));
  return (int) distance;
}
void printDistanceMaps(){
  int i;
  int j;
  for(i=0;i<21;i++){
    for(j=0;j<80;j++){
      if(i==0 || i==20 || j== 0 || j==79){
	printf(" ");
      }else{
	printf("%c",convertInt(NTDist[i][j].dist));
      }
    }
    printf("\n");
  }
  printf("\n\n");
   for(i=0;i<21;i++){
    for(j=0;j<80;j++){
      if(i==0 || i==20 || j== 0 || j==79){
	printf(" ");
      }else{
	printf("%c",convertInt(TDist[i][j].dist));
      }
    }
    printf("\n");
  }
}
char convertInt(int i){
  char temp;
  int j = i;
  if(i<10){
    j+=48;
  }else if(i<36){
    j+=87;
  }else if(i<62){
    j-=36;
    j+=65;
  }else{
    j = 32;
  }
  temp = j;
  return temp;
}


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
void printGrid();
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

  /*Main Loop for Non-Tunneling Path Finding*/
 
  //Point_t source = (*(Point_t *) binheap_remove_min(&h));
  //int x = source.x_pos;

  //int y = source.y_pos;
  /* for(i =0;i<21;i++){ */
  /*   for(j =0;j<80;j++){ */
  /*     *(int*)nodes[i][j]->datum = 1; */
  /*     binheap_decrease_key(&h,nodes[i][j]); */
  /*   } */
  /* } */

  
  /* Point_t *curr = ((Point_t*)binheap_remove_min(&h)); */
  /* int x = curr->x_pos; */
  /* int y = curr->y_pos; */
  /* printf("%d: %d \n",x,y); */
  /* for(i=y-1;i<y+2;i++){ */
  /*   for(j=x-1;j<x+2;j++){ */
  /*     printf("%d:%d ",j,i); */
  /*   } */
  /*   printf("\n"); */
  /* } */
  
  
  //printf("%d\n",*(int*)h.array[1]->datum);
  Point_t *curr;
  while((curr = ((Point_t*)binheap_remove_min(&h)))){
    //counter++;
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
  //  printf("%d\n",counter);
  printGrid();
  /* int counter =0; */
  /* while(binheap_peek_min(&h)){ */
  /*   printf("%d",((Point_t*)binheap_remove_min(&h))->dist); */
  /*   counter++; */
  /*   if(counter == 80){ */
  /*     printf("\n"); */
  /*     counter = 0; */
  /*   } */
  /* } */
  return 0;
}
int TPathFind(){
  printf("Will print out the Tunneling matrix of distances\n");
  return 0;
}
int dist(Point_t a, Point_t b){
  double distance; 
  distance = sqrt((a.x_pos - b.x_pos) * (a.x_pos - b.x_pos) + (a.y_pos-b.y_pos) *(a.y_pos-b.y_pos));
  return (int) distance;
}
void printGrid(){
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


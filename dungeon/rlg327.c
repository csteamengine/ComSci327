#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <endian.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include "dungeonGen.h"
#include "character.h"
#include "binheap.h"
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
      char seedToFile[50];
      sprintf(seedToFile,"%d",seed);
      fileName = strcat(seedToFile,".rlg327");
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
  createPlayer();
  printf("Seed: %d\n",seed);
  printDungeon();
  NTPathFind();
  TPathFind();
  free(roomP);
  return 0;  
}

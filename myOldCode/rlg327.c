#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <endian.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include "dungeon.h"
#include "character.h"
#include "binheap.h"
void initDungeon();
int updateDungeon();
int main(int argc, char *argv[]){
  int SaveBool = 0;   /* False == 0 */
  int LoadBool = 0;   /* False == 0 */
  char *save = "--save";
  char *load = "--load";
  char *nummon = "--nummon";
  int numMonsters = 0;
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
      fprintf(stderr,"Incorrect Command Line Parameters, must include filename to load.\n");
    }else if(strcmp(argv1,nummon) == 0){
      fprintf(stderr,"Incorrect Command Line Parameters, must include number of monsters\n");
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
      }else if(strcmp(argv1,nummon) == 0){
	seed = time(NULL);
	srand(seed);
	numMonsters = atoi(argv2);
	fileName = argv2;/*Make filename argv2*/
      }else{
	printf("%s\n%s\n",argv1,argv2);
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
    }else if(strcmp(argv1,load) == 0 && strcmp(argv2,nummon) ==0){
      fprintf(stderr,"Incorrect Command Line Parameters, must include file name and number of monsters\n");
    }else if(strcmp(argv1,save) == 0 && strcmp(argv2,nummon) ==0){
      SaveBool = 1;
      numMonsters = atoi(argv3);
      seed = time(NULL);
      srand(seed);
      sprintf(fileName,"%d",seed);
      strcat(fileName,".rlg327");
    }else{
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
    }
    
  }else if(argc == 5){
    char *argv1 = argv [1];
    char *argv2 = argv [2];
    char *argv3 = argv [3];
    char *argv4 = argv [4];
    if(strcmp(argv1,save) ==0 && strcmp(argv2,load) == 0){
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
    }else if(strcmp(argv1,save) == 0 && strcmp(argv2,nummon) ==0){
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
    }else if(strcmp(argv1,load) == 0 && strcmp(argv2,save) ==0){
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
    }else if(strcmp(argv1,load) == 0 && strcmp(argv2,nummon) ==0){
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
    }else if(strcmp(argv1,nummon) == 0 && strcmp(argv2,save) ==0){
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
    }else if(strcmp(argv1,nummon) == 0 && strcmp(argv2,load) ==0){
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
    }else if(strcmp(argv1,argv2) == 0){
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
    }else if(strcmp(argv1,save) == 0 && strcmp(argv3,load) == 0){
      fprintf(stderr,"Incorrect Command Line Parameters\n");
      return -1;
    }else if(strcmp(argv1,save) ==0 && strcmp(argv3,nummon) ==0){
      SaveBool = 1;
      seed = time(NULL);
      srand(seed);
      numMonsters = atoi(argv4);
      fileName = argv2;
    }else if(strcmp(argv1,load) ==0 && strcmp(argv3,nummon) ==0){
      LoadBool = 1;
      numMonsters = atoi(argv4);
      fileName = argv2;
    }else if(strcmp(argv1,nummon) ==0 && strcmp(argv3,save) ==0){
      SaveBool = 1;
      seed = time(NULL);
      srand(seed);
      numMonsters = atoi(argv2);
      fileName = argv4;
    }else if(strcmp(argv1,nummon) ==0 && strcmp(argv3,load) ==0){
      LoadBool = 1;
      numMonsters = atoi(argv2);
      fileName = argv4;
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
  initDungeon();
  createMonsters(numMonsters);
  while(1){
    sleep(1);
    if(updateDungeon() != 0){
      printDungeon();
      printf("%s You're a loser %s\n",RED,RESET);
      break;
    }
  }   
  free(roomP);
  free(monsters);
  return 0;  
}
void initDungeon(){
  createPlayer();
  NTPathFind();
  TPathFind();
  printDungeon();
}
int updateDungeon(){
  moveCharacter();
  NTPathFind();
  TPathFind();
  if(takeTurns() == -1){
    return -1;
  }
  printDungeon();
  return 0;
  //printDistanceMaps();   //To print out distance maps
}

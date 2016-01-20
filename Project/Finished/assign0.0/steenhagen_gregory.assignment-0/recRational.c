#include <stdio.h>
#include <stdlib.h>
int recRational(int b){

  if(b == 0){
    return 1;
  }else if(b%2 !=0){
    return recRational((b-1)/2);
  }else{
    int n = (b-2)/2;
    return recRational(n) + recRational(n+1);
  }
}

int main(int argc, char *argv[]){
  int arg;
  int num;
  int den;
  if(argc !=2){
    printf("Usage: recRational <number>/n");
    return -1;
  }
  arg = atoi(argv[1]);
  num = recRational(arg);
  den = recRational(arg+1);
  printf("%d / %d\n", num,den);
  return 0;
}

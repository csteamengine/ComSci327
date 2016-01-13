#include <stdio.h>
int arr[100000000];
int main(int argc, char *argv[]){
  int i;
  for(i = 0;i< sizeof(arr)/sizeof(int);i++){
    if(i == 0){
      arr[i] = 1;
    }else if(i%2 == 0){
      arr[i] = arr[(i/2)-1] + arr[(i/2)];
    }else{
      arr[i] = arr[(i-1)/2];
    }
  }
  for(i = 0; i < 10; i++){
    printf("%d\n",arr[i]);
  }
      
  return 0;
}

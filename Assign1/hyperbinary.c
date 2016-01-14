#include <stdio.h>
int arr[50000000];
int main(int argc, char *argv[]){
  int i;
  for(i = 0;i< sizeof(arr)/sizeof(int);i++){
    if(i == 0){
      arr[i] = 1;
      printf("%d\n",arr[i]);
    }else if(i%2 == 0){
      arr[i] = arr[(i/2)-1] + arr[(i/2)];
      printf("%d\n",arr[i]);
    }else{
      arr[i] = arr[(i-1)/2];
      printf("%d\n",arr[i]);
    }
  }
  for(i = sizeof(arr)/sizeof(int);i<100000000; i++){
    int num;
    if(i%2 == 0){
      num = arr[(i/2)-1] + arr[(i/2)];
      printf("%d\n",num);
    }else {
      num = arr[(i-1)/2];
      printf("%d\n",num);
    }
  }
  return 0;
}

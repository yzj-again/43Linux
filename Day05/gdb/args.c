#include<stdio.h>
int main(int argc, char *argv[]){
  printf("argc=%d\n",argc);
  for(int i=0;i<argc;i++){
    puts(argv[i]);
  }
}
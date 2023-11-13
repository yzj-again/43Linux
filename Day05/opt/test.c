#include<stdio.h>
int main(void){
#ifdef DEBUG
  puts("DEBUG is exists!");
#endif 
printf("add(3,4) = %d\n",add(3,4));
}
int add(int a, int b){
  return a+b;
}
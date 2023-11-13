#include<stdio.h>

int add(int a, int b); // 可以通过编译 gcc -c test.c -o test; 链接 gcc test.o -o test  error ld
int main(void){
	printf("add(3,4) = %d\n",add(3,4));
	return 0;
}

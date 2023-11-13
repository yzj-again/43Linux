#include<stdio.h>
void func(int i);
int main(void){
	int i = 10;
	int arr[3] = { 1, 2, 3 };
	int *p = NULL;
	arr[2] = 4;
	p = arr;
	func(i);
	for(int j=0;j<5;j++){
		puts("Hello World");
	}
	return 0;

}
void func(int i){
	printf("I am func,i = %d\n",i);
}

#include <learnCpp.h>
int global = 1; // 数据段
int main(void)
{
  int stack = 2;                       // 栈上
  int *p = (int *)malloc(sizeof(int)); // 堆上
  *p = 3;
  if (fork() == 0)
  {
    printf("I am child process, global = %d, stack = %d, heap = %d\n", global, stack, *p);
    ++global;
    ++stack;
    ++*p;
    printf("I am child process, global = %d, stack = %d, heap = %d\n", global, stack, *p);
  }
  else
  {
    sleep(5);
    printf("I am parent process, global = %d, stack = %d, heap = %d\n", global, stack, *p);
  }
  // I am child process, global = 1, stack = 2, heap = 3
  // I am child process, global = 2, stack = 3, heap = 4
  // I am parent process, global = 1, stack = 2, heap = 3
}
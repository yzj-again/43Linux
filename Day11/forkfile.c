#include <learnCpp.h>
int main(void)
{
  printf("hello");
  fork();
  printf(" world\n");
  return 0;
  // 1.printf("hello\n");
  //  hello
  //  world
  //  world
  // 2.printf("hello");
  // hello world
  // hello world
}
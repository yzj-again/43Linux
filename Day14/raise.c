#include <learnCpp.h>
void sigFunc(int num)
{
  printf("num is %d\n", num);
}
int main(void)
{
  signal(SIGINT, sigFunc);
  while (1)
  {
    getchar();
    raise(2);
  }
}
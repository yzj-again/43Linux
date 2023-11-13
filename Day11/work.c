#include <learnCpp.h>
int main(void)
{
  int i = 0;
  for (i = 0; i < 2; i++)
  {
    fork();
    printf("A\n");
  }
  // 无\n 8
  // 有\n 6
  return 0;
}
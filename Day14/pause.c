#include <learnCpp.h>
void sigFunc(int num)
{
  printf("num = %d\n", num);
}
int main(void)
{
  signal(SIGINT, sigFunc); // 注册2号信号
  pause();
}
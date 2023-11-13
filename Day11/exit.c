#include <learnCpp.h>
void func()
{
  // return; // 只能退出这个函数，不能退出程序
  // exit(123);
  // _exit(123);
  _Exit(124);
}
int main(void)
{
  printf("hello");
  func();
  return 100;
}
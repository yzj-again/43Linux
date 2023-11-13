#include <learnCpp.h>
void signalFn(int num);
int main(void)
{
  void (*ret)(int);
  ret = signal(SIGINT, signalFn);
  ERROR_CHECK(ret, SIG_ERR, "signal");
  // ret = signal(SIGQUIT, signalFn);
  // ERROR_CHECK(ret, SIG_ERR, "signal");
  char buf[100] = {0};
  read(STDIN_FILENO, buf, sizeof(buf));
  printf("buf = %s\n", buf);
}
void signalFn(int num)
{
  printf("num is %d\n", num);
  // printf("num is %d", num); 记得添加换行
  printf("before sleep,I am %d\n", num);
  sleep(3);
  printf("after sleep,I am %d\n", num);
}
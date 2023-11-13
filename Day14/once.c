#include <learnCpp.h>
void signalFn(int num);
int main(void)
{
  void (*ret)(int);
  ret = signal(SIGINT, signalFn);
  ERROR_CHECK(ret, SIG_ERR, "signal");
  signal(SIGINT, ret);
  char buf[100] = {0};
  read(STDIN_FILENO, buf, sizeof(buf));
  printf("buf = %s\n", buf);
}
void signalFn(int num)
{
  printf("num is %d\n", num);
  signal(SIGINT, SIG_DFL);
}
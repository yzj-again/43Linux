#include <learnCpp.h>
void sigFunc()
{
  // 解除屏蔽
}
void mysleep(int second)
{
  signal(SIGALRM, sigFunc);
  sigset_t set;
  sigset_t oldset;
  sigemptyset(&set);
  sigaddset(&set, SIGALRM);
  sigprocmask(SIG_SETMASK, &set, &oldset);
  printf("block\n");
  alarm(second);
  sigprocmask(SIG_SETMASK, &oldset, NULL);
  pause();
}
int main(void)
{
  mysleep(10);
}
#include <learnCpp.h>
int main(void)
{
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGQUIT);
  sigset_t oldset;
  sigprocmask(SIG_SETMASK, &set, &oldset); // 把3号信号加入屏蔽，oldset保存原来的屏蔽状况
  printf("I am going to sleep\n");
  sleep(10);
  printf("I wake up!\n");
  sigset_t pending;
  sigpending(&pending);
  if (sigismember(&pending, SIGQUIT))
  {
    printf("SIGQUIT is coming\n");
  }
  else
  {
    printf("SIGQUIT is not coming\n");
  }

  // 在睡眠过程中输入ctrl+\，不会终止，时间一到，此时第15行不会被打印
  // 恢复旧的
  sigprocmask(SIG_SETMASK, &oldset, NULL);
  printf("byebye!\n");
  return 0;
}
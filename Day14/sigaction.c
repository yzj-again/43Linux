#include <learnCpp.h>
void signalFn(int num);
void signalFn3(int num, siginfo_t *siginfo, void *p);
int main(void)
{
  struct sigaction act;
  memset(&act, sizeof(act), 0);
  // act.sa_handler = signalFn;
  act.sa_sigaction = signalFn3;
  // act.sa_flags = SA_RESTART | SA_SIGINFO | SA_RESETHAND;
  act.sa_flags = SA_NODEFER;
  int ret = sigaction(SIGINT, &act, NULL);
  ERROR_CHECK(ret, -1, "sigaction");
  char buf[100] = {0};
  read(STDIN_FILENO, buf, sizeof(buf));
  printf("buf = %s\n", buf);
}
void signalFn(int num)
{
  printf("num is %d\n", num);
}
void signalFn3(int num, siginfo_t *siginfo, void *p)
{
  printf("num is %d\n", num);
  printf("sender pid = %d\n", siginfo->si_pid);
}
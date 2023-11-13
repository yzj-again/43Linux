#include <learnCpp.h>
void sigFunc(int signum)
{
  time_t now = time(NULL);
  printf("%s\n", ctime(&now));
}
int main(void)
{
  sigFunc(0);
  signal(SIGALRM, sigFunc);
  alarm(10);
  pause();
}
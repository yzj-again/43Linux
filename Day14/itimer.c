#include <learnCpp.h>
void sigFunc(int signum)
{
  time_t now = time(NULL);
  puts(ctime(&now));
}
int main(void)
{
  struct itimerval itimer;
  itimer.it_value.tv_sec = 5;
  itimer.it_value.tv_usec = 0;
  itimer.it_interval.tv_sec = 1;
  itimer.it_interval.tv_usec = 0;
  signal(SIGALRM, sigFunc);
  setitimer(ITIMER_REAL, &itimer, NULL);
  sigFunc(0);
  while (1)
  {
    ;
  }
}
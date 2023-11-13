#include <learnCpp.h>
int main(void)
{
  if (fork() == 0)
  {
    printf("I am child process, pid = %d, pgid = %d\n", getpid(), getpgid(0));
    // setpgid(0, 0);
    printf("I am child process, pid = %d, pgid = %d\n", getpid(), getpgid(0));
    while (1)
      ;
  }
  else
  {
    printf("I am parent process, pid = %d, pgid = %d, ppid = %d\n", getpid(), getpgid(0), getppid());
    wait(NULL);
  }
}
#include <learnCpp.h>
int main()
{
  pid_t pid;
  pid = fork();
  if (pid == 0)
    printf("I am child,my pid = %d, ppid = %d\n", getpid(), getppid());
  else
  {
    printf("I am parent,my pid = %d, ppid = %d\n", getpid(), getppid());
    // sleep(1);
  }
  // return 0;
}

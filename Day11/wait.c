#include <learnCpp.h>
int main()
{
  pid_t pid;
  pid = fork();
  if (pid == 0) // 子
  {
    printf("I am child,my pid = %d, ppid = %d\n", getpid(), getppid());
    // return 123;
    // while (1)
    //   ;
    sleep(10);
  }
  else
  { // 父
    printf("I am parent,my pid = %d, ppid = %d\n", getpid(), getppid());
    int wsatus;
    while (1)
    {
      int ret = waitpid(-1, &wsatus, WNOHANG);
      if (ret == 0)
      {
        printf("not dead\n");
        sleep(1);
      }
      else
      {
        if (WIFEXITED(wsatus))
        {
          printf("normal exit!return value = %d\n", WEXITSTATUS(wsatus));
          // normal exit!return value = 123
        }
        else if (WIFSIGNALED(wsatus))
        {
          printf("abnormal exit!return terminal signal = %d\n", WTERMSIG(wsatus));
          // abnormal exit!return terminal signal = 9
        }
        break;
      }
    }
  }
}

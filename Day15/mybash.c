#include <learnCpp.h>
void sigFunc(int signum)
{
  printf("\n%s$", getcwd(NULL, 0));
  fflush(stdout);
}
int main(void)
{
  signal(SIGINT, sigFunc);
  while (1)
  {
    printf("%s$", getcwd(NULL, 0));
    fflush(stdout);
    char cmd[4096] = {0};
    read(STDIN_FILENO, cmd, sizeof(cmd));
    cmd[strlen(cmd) - 1] = 0;
    if (fork() == 0)
    {
      signal(SIGINT, SIG_DFL);
      char *argvector[100] = {0};
      argvector[0] = strtok(cmd, " ");
      int i = 1;
      while (1)
      {
        argvector[i] = strtok(NULL, " ");
        if (argvector[i] == NULL)
        {
          break;
        }
        i++;
      }

      execv(argvector[0], argvector);
    }
    else
    {
      wait(NULL);
    }
  }
}
#include <learnCpp.h>
void mysyetem(char *command);
int main(void)
{
  // system("./sleep");
  mysyetem("./add 3 4");
  return 0;
}
// 增量编写
void mysyetem(char *command)
{
  char buf[1024];
  strcpy(buf, command);
  char *word;
  char *argvec[10] = {0};
  word = strtok(buf, " ");
  argvec[0] = word;
  int i = 1;
  while ((word = strtok(NULL, " ")) != NULL)
  {
    argvec[i] = word;
    i++;
  }
  if (fork() == 0) // 子
  {
    execv(argvec[0], argvec);
  }
  else // 父进程
  {
    wait(NULL); // 参数NULL表示父进程不关心子进程的结束状态
  }
}
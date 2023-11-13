#include <learnCpp.h>
int main(void)
{
  int fd = open("file1", O_RDWR);
  if (fork() == 0)
  {
    write(fd, "hello", 5);
  }
  else
  { // 实际运行中父进程先执行。
    // 逻辑上不应该有这个假设，因为是并发执行
    sleep(1);
    write(fd, "world", 5);
  }
}
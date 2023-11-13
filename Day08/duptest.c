#include <learnCpp.h>

int main(int argc, char *argv[])
{
  int oldfd = open(argv[1], O_RDWR);
  int newfd = 16;

  int result = dup2(oldfd, newfd);

  if (result == -1)
  {
    perror("dup2 failed");
  }
  else
  {
    // 获取旧文件描述符的文件状态标志
    int old_flags = fcntl(oldfd, F_GETFL);
    // 获取新文件描述符的文件状态标志
    int new_flags = fcntl(newfd, F_GETFL);

    printf("Oldfd flags: %d\n", old_flags); // Oldfd flags: 32770
    printf("Newfd flags: %d\n", new_flags); // Newfd flags: 32770

    // 检查文件描述符是否相同
    if (old_flags == new_flags)
    {
      printf("dup2 successfully changed the file descriptor.\n");
    }
    else
    {
      printf("dup2 did not change the file descriptor.\n");
    }
  }

  return 0;
}
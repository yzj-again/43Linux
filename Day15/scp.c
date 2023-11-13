#include <learnCpp.h>
int main(void)
{
  int fds[2];
  pipe(fds);
  // 父读文件 写管道
  // 子读管道 写文件
  if (fork() == 0)
  {
    close(fds[1]); // 子进程关闭写端
    int fd = open("file2", O_CREAT | O_RDWR | O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "open");
    char buf[4096] = {0};
    // read 读管道会阻塞；而读文件则不会
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      int ret = read(fds[0], buf, sizeof(buf));
      ERROR_CHECK(ret, -1, "read");
      if (ret == 0)
      {
        break;
      }
      write(fd, buf, ret);
    }
    close(fds[0]);
  }
  else
  {
    close(fds[0]); // 父进程关闭读端
    int fd = open("file1", O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    char buf[4096];
    while (1)
    {
      memset(buf, 0, sizeof(buf));
      int ret = read(fd, buf, sizeof(buf));
      ERROR_CHECK(ret, -1, "read");
      if (ret == 0)
      {
        break;
      }
      write(fds[1], buf, ret);
    }
    close(fds[1]);
    wait(NULL);
  }
}
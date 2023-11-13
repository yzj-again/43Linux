#include <learnCpp.h>
int main()
{
  int fd[2];
  pipe(fd);
  if (fork() == 0)
  {
    close(fd[1]);
    char buf[10] = {0};
    struct iovec iov[1];
    iov[0].iov_base = buf;
    iov[0].iov_len = sizeof(buf);
    readv(fd[0], iov, 1);
    puts(buf);
    exit(0);
  }
  else
  {
    close(fd[0]);
    char buf[10] = "hello";
    struct iovec iov[1];
    iov[0].iov_base = buf;
    iov[0].iov_len = strlen(buf);
    writev(fd[1], iov, 1);
    wait(NULL);
  }
}
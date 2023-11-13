#include <learnCpp.h>
int main(void)
{
  int pipefds1[2];
  int pipefds2[2];
  pipe(pipefds1);
  pipe(pipefds2);
  // pipefds1 父写 子读
  // pipefds2 父读 子写
  if (fork() == 0) // 子进程
  {
    close(pipefds1[1]);
    close(pipefds2[0]);
    write(pipefds2[1], "msg from child", 14);
    char buf[1024] = {0};
    read(pipefds1[0], buf, sizeof(buf));
    puts(buf);
  }
  else
  { // read是阻塞的行为，总是子进程写完数据后才能读取到 阻塞实现同步
    close(pipefds1[0]);
    close(pipefds2[1]);
    char buf[1024] = {0};
    read(pipefds2[0], buf, sizeof(buf));
    puts(buf);
    write(pipefds1[1], "msg from parent", 15);
    wait(NULL);
  }
}
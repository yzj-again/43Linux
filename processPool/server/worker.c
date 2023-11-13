#include "worker.h"
#include "head.h"
int makeChild(workerData_t *workerArr, int workerNum)
{
  pid_t pid;
  int pipeFd[2];
  for (int i = 0; i < workerNum; i++)
  {
    socketpair(AF_LOCAL, SOCK_STREAM, 0, pipeFd); // 每次创建一个新的管道文件
    pid = fork();
    if (pid == 0)
    {
      // 子进程，确保不会脱离if
      printf("1");
      close(pipeFd[0]);
      eventHandler(pipeFd[1]);
    }
    // 父进程，记录pid
    close(pipeFd[1]);
    printf("pipeFd = %d, pid = %d\n", pipeFd[0], pid);
    workerArr[i].pid = pid;
    workerArr[i].pipeFd = pipeFd[0];
    workerArr[i].status = FREE;
  }
}
int eventHandler(int pipeFd)
{
  while (1)
  {
    int netFd;
    int exitFlag;
    // 子进程拿到父进程发送过来的为文件描述符netFd
    recvFd(pipeFd, &netFd, &exitFlag);
    if (exitFlag == 1)
    {
      puts("I am going to die\n");
      exit(0);
    }
    printf("i got mask\n");
    // done
    transFile(netFd);
    printf("i finish mask\n");
    pid_t pid = getpid();
    write(pipeFd, &pid, sizeof(pid));
    // 子进程发消息，父进程epoll_wait会就绪
    close(netFd);
  }
}

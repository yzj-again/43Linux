#include <learnCpp.h>
#include "worker.h"
#include "head.h"
workerData_t *workerArr;
int workerNum;
void sigFunc(int signum)
{
  printf("signal = %d\n", signum);
  for (int i = 0; i < workerNum; i++)
  {
    kill(workerArr[i].pid, SIGUSR1);
  }
  // 收尸
  for (int j = 0; j < workerNum; j++)
  {
    wait(NULL);
  }
  puts("process pool is over!");
  exit(0);
}
int main(int argc, char *argv[])
{
  // ./server 192.168.150.121 1234 3
  // 1.创建很多子进程
  workerNum = atoi(argv[3]);
  // 给子进程先分配空间
  // workerData_t *workerArr = (workerData_t *)calloc(workerNum, sizeof(workerData_t));
  workerArr = (workerData_t *)calloc(workerNum, sizeof(workerData_t));
  makeChild(workerArr, workerNum);
  // 父进程注册信号
  signal(SIGUSR1, sigFunc);
  // 初始化tcp连接
  int sockFd;
  tcpInit(&sockFd, argv[1], argv[2]);
  // 用epoll把tcp连接和子进程管理起来
  int epollFd = epoll_create(1);
  // 把socket加入监听，还要监听子进程管道
  epollAdd(sockFd, epollFd);
  for (int i = 0; i < workerNum; i++)
  {
    epollAdd(workerArr[i].pipeFd, epollFd);
  }
  // 最大容量
  int listenSize = workerNum + 1;
  struct epoll_event *readyArr = (struct epoll_event *)calloc(listenSize, sizeof(struct epoll_event));
  while (1)
  {
    int readyNum = epoll_wait(epollFd, readyArr, listenSize, -1);
    printf("epoll_wait ready\n");
    for (int i = 0; i < readyNum; i++)
    {
      if (readyArr[i].data.fd == sockFd)
      { // 有客户端连接到来
        puts("client connect");
        int netFd = accept(sockFd, NULL, NULL);
        ERROR_CHECK(netFd, -1, "accept");
        for (int j = 0; j < workerNum; j++)
        {
          if (workerArr[j].status == FREE)
          {
            printf("%d worker got a job, pid = %d\n", j, workerArr[j].pid);
            // 通过管道发送给子进程
            sendFd(workerArr[j].pipeFd, netFd);
            close(netFd);
            workerArr[j].status = BUSY;
            break;
          }
        }
      }
      else
      {
        puts("one worker finish work");
        int j;
        for (j = 0; j < workerNum; j++)
        { // 找谁给我发消息了
          if (readyArr[i].data.fd == workerArr[j].pipeFd)
          {
            pid_t pid;
            // 接收子进程发来的pid
            int ret = read(workerArr[j].pipeFd, &pid, sizeof(pid));
            printf("%d worker finish his job, pid = %d\n", j, pid);
            workerArr[j].status == FREE;
            break;
          }
        }
      }
    }
  }
}
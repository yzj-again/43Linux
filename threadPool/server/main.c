#include "threadPool.h"
#include <learnCpp.h>
int threadPoolInit(threadPool_t *pThreadPool, int workerNumber)
{
  pThreadPool->threadNumber = workerNumber;
  pThreadPool->tid = (pthread_t *)calloc(workerNumber, sizeof(pthread_t));
  pThreadPool->taskQueue.pFront = NULL;
  pThreadPool->taskQueue.pRear = NULL;
  pThreadPool->taskQueue.size = 0;
  // 初始化锁和信号量
  pthread_mutex_init(&pThreadPool->taskQueue.mutex, NULL);
  pthread_cond_init(&pThreadPool->taskQueue.cond, NULL);
}
int main(int argc, char *argv[])
{
  // ./server 192.168.150.121 1234 3
  int workerNumber = atoi(argv[3]);
  // 为线程池的任务队列、子线程的tid申请内存
  threadPool_t threadPool;
  // 初始化线程池
  threadPoolInit(&threadPool, workerNumber);
  // 创建若干个子线程
  makeWorker(&threadPool);
  // 主线程初始化tcp连接
  int sockFd;
  tcpInit(&sockFd, argv[1], argv[2]);
  // epoll监听sockFd
  int epollFd = epoll_create(1);
  epollAdd(sockFd, epollFd);
  // 就绪事件队列
  struct epoll_event readyArr[2];
  while (1)
  {
    int readyNum = epoll_wait(epollFd, readyArr, 2, -1);
    printf("epoll_wait return!\n");
    for (int i = 0; i < readyNum; i++)
    {
      if (readyArr[i].data.fd == sockFd)
      {
        // 有客户端连接过来
        int netFd = accept(sockFd, NULL, NULL);
        // 交给子线程--不用sendMsg、recvMsg，都是共享的
        // 主线程发，子线程执行，但子线程是先等待
        // 先加锁--生产一个任务
        pthread_mutex_lock(&threadPool.taskQueue.mutex);
        // 入队
        taskEnqueue(&threadPool.taskQueue, netFd);
        printf("New task add!\n");
        // 通知处于唤醒队列的子线程
        // 数值上一样，不能关掉
        pthread_cond_signal(&threadPool.taskQueue.cond);
        pthread_mutex_unlock(&threadPool.taskQueue.mutex);
      }
    }
  }
}
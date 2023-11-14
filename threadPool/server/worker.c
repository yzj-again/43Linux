#include "threadPool.h"
void *handleEvent(void *arg)
{
  threadPool_t *pThreadPool = (threadPool_t *)arg;
  int netFd;
  while (1)
  {
    // 加锁
    printf("I am free!tid = %lus\n", pthread_self());
    pthread_mutex_lock(&pThreadPool->taskQueue.mutex);
    while (pThreadPool->taskQueue.size == 0)
    {
      // 空的-等待
      // 三个都在等，锁放出来了
      pthread_cond_wait(&pThreadPool->taskQueue.cond, &pThreadPool->taskQueue.mutex);
    }
    // 现在子线程苏醒了 cond 自带队列
    netFd = pThreadPool->taskQueue.pFront->netFd; // 拿到了队首的文件描述符
    // 出队
    taskDequeue(&pThreadPool->taskQueue);
    // 解锁
    pthread_mutex_unlock(&pThreadPool->taskQueue.mutex);
    printf("I am working! tid = %lu\n", pthread_self());
    transFile(netFd);
    printf("done\n");
    close(netFd);
  }
}
int makeWorker(threadPool_t *pThreadPool)
{
  // 这个指针里有所有子线程的tid
  for (int i = 0; i < pThreadPool->threadNumber; i++)
  {
    pthread_create(&pThreadPool->tid[i], NULL, handleEvent, (void *)pThreadPool);
  }
}
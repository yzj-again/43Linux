#include <learnCpp.h>
typedef struct task_s
{
  int netFd; // 传递文件描述符
  struct task_s *pNext;
} task_t;
typedef struct taskQueue_s
{
  task_t *pFront; // 队首指针
  task_t *pRear;  // 队尾指针
  int size;       // 队列现在的长度
  pthread_mutex_t mutex;
  pthread_cond_t cond;
} taskQueue_t;
// 定义线程池
typedef struct threadPool_s
{
  pthread_t *tid;   // 子线程的数组
  int threadNumber; // 子线程的数量
  taskQueue_t taskQueue;
} threadPool_t;
typedef struct train_s
{
  int length;
  char buf[1000];
} train_t;
int taskEnqueue(taskQueue_t *pTaskQueue, int netFd);
int taskDequeue(taskQueue_t *pTaskQueue);
int threadPoolInit(threadPool_t *pThreadPool, int workerNumber);
int makeWorker(threadPool_t *pThreadPool);
int tcpInit(int *pSockFd, char *ip, char *port);
int epollAdd(int fd, int epollFd);
int epollDelete(int fd, int epollFd);
int transFile(int netFd);
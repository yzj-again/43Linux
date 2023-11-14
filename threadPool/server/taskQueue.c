#include "threadPool.h"
int taskEnqueue(taskQueue_t *pTaskQueue, int netFd)
{
  task_t *pTask = (task_t *)calloc(1, sizeof(task_t)); // 在堆上分配内存
  pTask->netFd = netFd;
  if (pTaskQueue->size == 0)
  {
    pTaskQueue->pFront = pTask;
    pTaskQueue->pRear = pTask;
  }
  else
  { // 链表的尾插法
    pTaskQueue->pRear->pNext = pTask;
    pTaskQueue->pRear = pTask;
  }
  ++pTaskQueue->size;
  return 0;
}
int taskDequeue(taskQueue_t *pTaskQueue)
{
  task_t *pCur = pTaskQueue->pFront;
  pTaskQueue->pFront = pCur->pNext;
  free(pCur);
  --pTaskQueue->size;
  return 0;
}
#include <learnCpp.h>
#define NUM 10
typedef struct queue_s
{
  int elem[NUM];
  int front; // front表示队首的下标
  int rear;  // rear表示下一个要入队的元素的下标
  int size;
} queue_t;
int cnt = 0;
// 共享资源
typedef struct shareRes_s
{
  queue_t queue;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
} shareRes_t;
void *producer(void *arg)
{
  shareRes_t *pShareRes = (shareRes_t *)arg;
  while (1)
  {
    pthread_mutex_lock(&pShareRes->mutex);
    if (pShareRes->queue.size == 10)
    {
      pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex);
    }
    // 没有满，生产商品
    pShareRes->queue.elem[pShareRes->queue.rear] = cnt++;
    pShareRes->queue.rear = (pShareRes->queue.rear + 1) % NUM;
    ++pShareRes->queue.size;
    printf("producer size = %d, front = %d,rear = %d\n",
           pShareRes->queue.size,
           pShareRes->queue.elem[pShareRes->queue.front],
           pShareRes->queue.elem[(pShareRes->queue.rear - 1 + NUM) % NUM]);
    if (pShareRes->queue.size == 1)
    {
      pthread_cond_signal(&pShareRes->cond);
    }
    pthread_mutex_unlock(&pShareRes->mutex);
    usleep(500000);
  }
}
void *consumer(void *arg)
{
  shareRes_t *pShareRes = (shareRes_t *)arg;
  while (1)
  {
    pthread_mutex_lock(&pShareRes->mutex);
    if (pShareRes->queue.size == 0)
    {
      pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex);
    }
    pShareRes->queue.front = (pShareRes->queue.front + 1) % NUM;
    --pShareRes->queue.size;
    printf("consumer size = %d, front = %d,rear = %d\n",
           pShareRes->queue.size,
           pShareRes->queue.elem[pShareRes->queue.front],
           pShareRes->queue.elem[(pShareRes->queue.rear - 1 + NUM) % NUM]);
    if (pShareRes->queue.size == 9)
    {
      pthread_cond_signal(&pShareRes->cond);
    }
    pthread_mutex_unlock(&pShareRes->mutex);
    sleep(1);
  }
}
int main(void)
{
  shareRes_t shareRes;
  printf("%ld", sizeof(shareRes.queue.elem));
  memset(&shareRes.queue.elem, 0, sizeof(shareRes.queue));
  pthread_mutex_init(&shareRes.mutex, NULL);
  pthread_cond_init(&shareRes.cond, NULL);
  // 创建两个线程
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, producer, (void *)&shareRes);
  pthread_create(&tid2, NULL, consumer, (void *)&shareRes);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  // 销毁
  pthread_mutex_destroy(&shareRes.mutex);
  pthread_cond_destroy(&shareRes.cond);
}
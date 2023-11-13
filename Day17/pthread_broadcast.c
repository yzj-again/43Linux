#include <learnCpp.h>
typedef struct shareRes_s
{
  int cnt;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
} shareRes_t;
void *threadFunc(void *arg)
{
  shareRes_t *pShareRes = (shareRes_t *)arg;
  pthread_mutex_lock(&pShareRes->mutex);
  while (pShareRes->cnt == 0)
  {
    pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex);
  }
  printf("cnt = %d\n", pShareRes->cnt); // 一定要注意缓冲区的问题
  pShareRes->cnt = pShareRes->cnt - 1;
  printf("cnt = %d\n", pShareRes->cnt);
  pthread_mutex_unlock(&pShareRes->mutex);
  pthread_exit(NULL);
}
int main(void)
{
  // 初始化锁和条件变量
  shareRes_t shareRes;
  pthread_mutex_init(&shareRes.mutex, NULL);
  pthread_cond_init(&shareRes.cond, NULL);
  shareRes.cnt = 0;
  // 创建一个子线程
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, threadFunc, (void *)&shareRes);
  pthread_create(&tid2, NULL, threadFunc, (void *)&shareRes);

  // 先执行一个事件，然后唤醒等待在条件变量上的某个线程
  sleep(1); // 尽管hello等待了1s才打印出来
  pthread_mutex_lock(&shareRes.mutex);
  shareRes.cnt = 1;
  // 唤醒子线程
  // pthread_cond_signal(&shareRes.cond);
  pthread_cond_broadcast(&shareRes.cond);
  pthread_mutex_unlock(&shareRes.mutex);
  // 等待子线程的终止 销毁锁和条件变量
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_cond_destroy(&shareRes.cond);
  pthread_mutex_destroy(&shareRes.mutex);
}
#include <learnCpp.h>
typedef struct shareRes_s
{
  int flag;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
} shareRes_t;
void *threadFunc(void *arg)
{
  shareRes_t *pShareRes = (shareRes_t *)arg;
  // 先加锁
  pthread_mutex_lock(&pShareRes->mutex);
  // 只有在加锁的状态下才能使用wait
  if (pShareRes->flag == 0)
  {
    pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex);
  }
  // 从wait中唤醒，说明前面的事件已经完成
  puts("world");
  pthread_mutex_unlock(&pShareRes->mutex);
  pthread_exit(NULL);
}
int main(void)
{
  // 初始化锁和条件变量
  shareRes_t shareRes;
  pthread_mutex_init(&shareRes.mutex, NULL);
  pthread_cond_init(&shareRes.cond, NULL);
  shareRes.flag = 0;
  // 创建一个子线程
  pthread_t tid;
  pthread_create(&tid, NULL, threadFunc, (void *)&shareRes);

  // 先执行一个事件，然后唤醒等待在条件变量上的某个线程
  sleep(1); // 尽管hello等待了1s才打印出来
  // pthread_mutex_lock(&shareRes.mutex);
  puts("hello");
  shareRes.flag = 1;
  // 唤醒子线程
  pthread_cond_signal(&shareRes.cond);
  sleep(1); // 先睡再打印子线程，因为子线程拿不到锁
  // 先有hello等一秒钟再打印world
  pthread_mutex_lock(&shareRes.mutex);
  // 解锁步骤放后面一点
  pthread_mutex_unlock(&shareRes.mutex);
  // 等待子线程的终止 销毁锁和条件变量
  pthread_join(tid, NULL);
  pthread_cond_destroy(&shareRes.cond);
  pthread_mutex_destroy(&shareRes.mutex);
}
#include <learnCpp.h>
typedef struct shareRes_s
{
  int flag;
  int trainTicket;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
} shareRes_t;
void *sellTicket1(void *arg)
{
  sleep(1); // 确保addTicket能够持有锁（因为wait后会放出锁）
  shareRes_t *pShareRes = (shareRes_t *)arg;
  while (1)
  {
    sleep(1);
    // 这里仍然是拿到锁之后再进行操作，避免干扰
    pthread_mutex_lock(&pShareRes->mutex);
    if (pShareRes->trainTicket > 0)
    {
      printf("Before 1 sell ticket = %d\n", pShareRes->trainTicket);
      pShareRes->trainTicket--;
      printf("After 1 sell ticket = %d\n", pShareRes->trainTicket);
      if (pShareRes->trainTicket == 0 && pShareRes->flag == 0)
      {
        // 如果买完票后且从来没有放过票
        pShareRes->flag = 1;
        pthread_cond_signal(&pShareRes->cond);
      }
      else if (pShareRes->trainTicket == 0 && pShareRes->flag != 0)
      {
        // 如果买完票，且已经放过票，终止线程
        pthread_mutex_unlock(&pShareRes->mutex);
        break;
      }
    }
    else
    {
      pthread_mutex_unlock(&pShareRes->mutex);
      break;
    }
    pthread_mutex_unlock(&pShareRes->mutex);
  }
  pthread_exit(NULL);
}
void *sellTicket2(void *arg)
{
  sleep(1); // 确保addTicket能够持有锁（因为wait后会放出锁）
  shareRes_t *pShareRes = (shareRes_t *)arg;
  while (1)
  {
    sleep(1);
    // 这里仍然是拿到锁之后再进行操作，避免干扰
    pthread_mutex_lock(&pShareRes->mutex);
    if (pShareRes->trainTicket > 0)
    {
      printf("Before 2 sell ticket = %d\n", pShareRes->trainTicket);
      pShareRes->trainTicket--;
      printf("After 2 sell ticket = %d\n", pShareRes->trainTicket);
      if (pShareRes->trainTicket == 0 && pShareRes->flag == 0)
      {
        // 如果买完票后且从来没有放过票
        pShareRes->flag = 1;
        pthread_cond_signal(&pShareRes->cond);
      }
      else if (pShareRes->trainTicket == 0 && pShareRes->flag != 0)
      {
        // 如果买完票，且已经放过票，终止线程
        pthread_mutex_unlock(&pShareRes->mutex);
        break;
      }
    }
    else
    {
      pthread_mutex_unlock(&pShareRes->mutex);
      break;
    }
    pthread_mutex_unlock(&pShareRes->mutex);
  }
  pthread_exit(NULL);
}
void *addTicket(void *arg)
{
  shareRes_t *pShareRes = (shareRes_t *)arg;
  pthread_mutex_lock(&pShareRes->mutex);
  if (pShareRes->flag != 1)
  {
    pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex);
  }
  printf("add ticket!\n");
  pShareRes->trainTicket = 10;
  pthread_mutex_unlock(&pShareRes->mutex);
  pthread_exit(NULL);
}
int main(void)
{
  shareRes_t shareRes;
  shareRes.trainTicket = 20; // 初始票数是20
  shareRes.flag = 0;         // 最开始不需要放票
  pthread_mutex_init(&shareRes.mutex, NULL);
  pthread_cond_init(&shareRes.cond, NULL);
  pthread_t tid1, tid2, tid3;
  pthread_create(&tid1, NULL, sellTicket1, (void *)&shareRes);
  pthread_create(&tid2, NULL, sellTicket2, (void *)&shareRes);
  pthread_create(&tid3, NULL, addTicket, (void *)&shareRes);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  pthread_mutex_destroy(&shareRes.mutex);
  pthread_cond_destroy(&shareRes.cond);
}
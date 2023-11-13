#include <learnCpp.h>
typedef struct shareRes_s
{
  pthread_mutex_t mutex;
  int trainTicket;
} shareRes_t;
void *sellTicket1(void *arg)
{
  int count = 0;
  shareRes_t *pShareRes = (shareRes_t *)arg;
  while (1)
  {
    pthread_mutex_lock(&pShareRes->mutex);
    if (pShareRes->trainTicket <= 0)
    {
      pthread_mutex_unlock(&pShareRes->mutex);
      break; // break 可以退出进程
    }
    printf("before 1 sell ticket,num = %d\n", pShareRes->trainTicket);
    --pShareRes->trainTicket;
    ++count;
    printf("after 1 sell ticket,num = %d\n", pShareRes->trainTicket);
    pthread_mutex_unlock(&pShareRes->mutex);
    // sleep(1);
  }
  printf("sell ticket = %d\n", count);
}
void *sellTicket2(void *arg)
{
  int count = 0;
  shareRes_t *pShareRes = (shareRes_t *)arg;
  while (1)
  {
    pthread_mutex_lock(&pShareRes->mutex);
    if (pShareRes->trainTicket <= 0)
    {
      pthread_mutex_unlock(&pShareRes->mutex);
      break; // break 可以退出进程
    }
    printf("before 2 sell ticket,num = %d\n", pShareRes->trainTicket);
    --pShareRes->trainTicket;
    ++count;
    printf("after 2 sell ticket,num = %d\n", pShareRes->trainTicket);
    pthread_mutex_unlock(&pShareRes->mutex);
    // sleep(1);
  }
  printf("sell ticket = %d\n", count);
}
int main(void)
{
  shareRes_t shareRes;
  shareRes.trainTicket = 2000;
  pthread_mutex_init(&shareRes.mutex, NULL);
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, sellTicket1, (void *)&shareRes);
  pthread_create(&tid2, NULL, sellTicket2, (void *)&shareRes);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_mutex_destroy(&shareRes.mutex);
}
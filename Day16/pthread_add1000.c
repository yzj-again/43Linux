#include <learnCpp.h>
#define NUM 10000000
void *threadFunc(void *arg)
{
  printf("I am child thread, tid = %lu\n", pthread_self());
  int *pCount = (int *)arg;
  for (int i = 0; i < NUM; i++)
  {
    ++*pCount;
  }
}
int main(void)
{
  printf("I am main thread, tid = %lu\n", pthread_self());
  pthread_t tid;
  int count = 0;
  int ret = pthread_create(&tid, NULL, threadFunc, (void *)&count);
  THREAD_ERROR_CHECK(ret, "pthread_create");
  for (int i = 0; i < NUM; i++)
  {
    ++count;
  }
  pthread_join(tid, NULL);
  printf("count = %d\n", count);
  return 0;
}
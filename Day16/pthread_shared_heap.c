#include <learnCpp.h>
void *threadFunc(void *arg)
{
  printf("I am child thread, tid = %lu\n", pthread_self());
  int *pHead = (int *)arg;
  *pHead = 100;
  printf("child thread, tid = %d\n", *pHead);
}
int main(void)
{
  printf("I am main thread, tid = %lu\n", pthread_self());
  int *p = (int *)malloc(sizeof(int));
  *p = 200;
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, threadFunc, (void *)p);
  THREAD_ERROR_CHECK(ret, "pthread_create");
  sleep(1);
  printf("main thread, tid = %d\n", *p);
  return 0;
}
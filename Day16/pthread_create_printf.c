#include <learnCpp.h>
void *threadFunc(void *)
{
  printf("I am child thread, tid = %lu\n", pthread_self());
}
int main(void)
{
  printf("I am main thread, tid = %lu\n", pthread_self());
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, threadFunc, NULL);
  THREAD_ERROR_CHECK(ret, "pthread_create");
  // sleep(1);
  return 0;
}
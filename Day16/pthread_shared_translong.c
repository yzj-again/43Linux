#include <learnCpp.h>
void *threadFunc(void *arg)
{
  printf("I am child thread, tid = %lu\n", pthread_self());
  long i = (long)arg;
  i = 100;
  printf("child thread, arg = %ld\n", i);
}
int main(void)
{
  printf("I am main thread, tid = %lu\n", pthread_self());
  long i = 1;
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, threadFunc, (void *)i);
  THREAD_ERROR_CHECK(ret, "pthread_create");
  sleep(1);
  printf("main thread, tid = %ld\n", i);
  return 0;
}
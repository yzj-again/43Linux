#include <learnCpp.h>
int global = 10;
void *threadFunc(void *)
{
  printf("I am child thread, tid = %lu\n", pthread_self());
  printf("In child thread, global = %d\n", global);
}
int main(void)
{
  printf("I am main thread, tid = %lu\n", pthread_self());
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, threadFunc, NULL);
  THREAD_ERROR_CHECK(ret, "pthread_create");
  sleep(1);
  global = 200;
  printf("In main thread, global = %d\n", global);
  sleep(1);
  return 0;
}
#include <learnCpp.h>
void *threadFunc(void *)
{
  printf("I am child thread, tid = %lu\n", pthread_self());
  printf("end\n");
  pthread_exit((void *)0);
}
int main(void)
{
  printf("I am main thread, tid = %lu\n", pthread_self());
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, threadFunc, NULL);
  THREAD_ERROR_CHECK(ret, "pthread_create");
  pthread_cancel(tid);
  void *retVal;
  pthread_join(tid, &retVal);
  printf("child thread return value = %ld\n", (long)retVal);
  // 0 或 -1cancel
  return 0;
}
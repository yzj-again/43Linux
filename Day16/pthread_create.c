#include <learnCpp.h>
void *threadFunc(void *)
{
  // printf("I am child thread, tid = %lu\n", pthread_self());
  while (1)
  {
    sleep(1);
  }
}
int main(void)
{
  // printf("I am main thread, tid = %lu\n", pthread_self());
  pthread_t tid;
  for (int i = 0;; i++)
  {
    int ret = pthread_create(&tid, NULL, threadFunc, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");
    if (ret != 0)
    {
      printf("i = %d\n", i);
      break;
    }
  }
  // sleep(1);
  return 0;
}
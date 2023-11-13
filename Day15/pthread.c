#include <learnCpp.h>
void *threadFunc(void *arg)
{
  // 子线程的main函数
  printf("I am child thread,tid = %lu\n", pthread_self());
}
int main(void)
{
  printf("I am main thread,tid = %lu\n", pthread_self());
  pthread_t tid;
  pthread_create(&tid, NULL, threadFunc, NULL);
  // sleep(1);
  // return 0;
  _exit(0); // 1行或者2行
}
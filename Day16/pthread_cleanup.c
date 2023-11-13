#include <learnCpp.h>
void clean1(void *arg)
{
  printf("I am clean1\n");
  free(arg);
}
void clean2(void *arg)
{
  printf("I am clean2\n");
  free(arg);
}
void *threadFunc(void *)
{
  printf("I am child thread, tid = %lu\n", pthread_self());
  // pthread_exit(NULL);                // 在执行完第14行后，发送取消信号
  int *p1 = (int *)malloc(sizeof(int)); // 申请资源后，马上将对应的清理行为压栈
  pthread_cleanup_push(clean1, p1);     // cleanup_push不是取消点.malloc是取消点
  // pthread_exit(NULL);
  int *p2 = (int *)malloc(sizeof(int));
  pthread_cleanup_push(clean2, p2);
  // pthread_exit(NULL); // 执行完第19行后，发送取消信号,pthread_exit是立即终止
  // pthread_cleanup_pop(1);
  // pthread_cleanup_pop(1);
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  // clean1(p1);
  // clean2(p2);
  pthread_exit(NULL);
}
int main(void)
{
  printf("I am main thread, tid = %lu\n", pthread_self());
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, threadFunc, NULL);
  THREAD_ERROR_CHECK(ret, "pthread_create");
  pthread_join(tid, NULL);
  return 0;
}
#include <learnCpp.h>
void *threadFunc(void *)
{
  printf("I am child thread, tid = %lu\n", pthread_self());
  // return (void *)123; // 用数字当作一个地址
  pthread_exit((void *)123);
}
int main(void)
{
  printf("I am main thread, tid = %lu\n", pthread_self());
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, threadFunc, NULL);
  THREAD_ERROR_CHECK(ret, "pthread_create");
  // long retVal;                         // 申请了8个字节
  // pthread_join(tid, (void **)&retVal); // 传这片地址的地址，强转成void **
  //  在函数中修改主调函数的地址的值，如果只传地址的副本过去，虽然都指向同一片地址空间
  //  但在函数销毁时，副本指向的内容也会被销毁，副本本身也会被销毁
  // printf("ret = %ld\n", retVal);
  // void *retVal; // 申请了8个字节
  // pthread_join(tid, &retVal);
  // printf("ret = %ld\n", (long)retVal);
  // 不管死活，不获取子线程的终止状态，阻塞线程直到tid线程终止
  pthread_join(tid, NULL);
  return 0;
}
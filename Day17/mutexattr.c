#include <learnCpp.h>
int main(void)
{
  pthread_mutex_t mutex;
  pthread_mutexattr_t mutexattr;
  pthread_mutexattr_init(&mutexattr); // 初始化锁的属性
  // pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_NORMAL);
  // pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK); // 检错锁 对同一把锁加锁，第二次会报错
  pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE); // 可重入锁，对同一把锁加锁，第二次是成功
  pthread_mutex_init(&mutex, &mutexattr);                         // 如果第二个参数是NULL，表示以默认形式初始化锁
  // PTHREAD_MUTEX_NORMAL == NULL
  int ret = pthread_mutex_lock(&mutex); // 第一次加锁
  THREAD_ERROR_CHECK(ret, "pthread_mutex_lock 1");
  puts("lock one time");
  ret = pthread_mutex_lock(&mutex); // 第二次加锁
  THREAD_ERROR_CHECK(ret, "pthread_mutex_lock 2");
  puts("lock two time");
  pthread_mutex_destroy(&mutex);
  return 0;
}
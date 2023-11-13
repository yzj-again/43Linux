#include <learnCpp.h>
int main(void)
{
  // pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;静态初始化
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);        // 如果第二个参数是NULL，表示以默认形式初始化锁
  int ret = pthread_mutex_trylock(&mutex); // 第一次加锁
  THREAD_ERROR_CHECK(ret, "pthread_mutex_lock");
  puts("lock one time");
  ret = pthread_mutex_trylock(&mutex); // 第二次加锁
  THREAD_ERROR_CHECK(ret, "pthread_mutex_trylock");
  puts("lock two time");
  pthread_mutex_destroy(&mutex);
  return 0;
}
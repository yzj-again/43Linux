#include <learnCpp.h>
int main(void)
{
  // pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;静态初始化
  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL); // 如果第二个参数是NULL，表示以默认形式初始化锁
  pthread_mutex_lock(&mutex);       // 第一次加锁
  puts("lock one time");
  pthread_mutex_lock(&mutex); // 第二次加锁
  puts("lock two time");
  pthread_mutex_destroy(&mutex);
  return 0;
}
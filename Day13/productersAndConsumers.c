#include <learnCpp.h>
#define NUM 1000000
int main(void)
{
  key_t key = ftok("file1", 1);
  int shmid = shmget(key, 4096, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
  int *p = (int *)shmat(shmid, NULL, 0);
  ERROR_CHECK(p, (void *)-1, "shmat");
  p[0] = 10;                                     // p[0]表示仓库个数
  p[1] = 0;                                      // p[1]表示商品个数
  int semid = semget(1000, 1, IPC_CREAT | 0600); // 创建一个信号量，初始值是1
  ERROR_CHECK(semid, -1, "semget");
  int ret = semctl(semid, 0, SETVAL, 1);
  ERROR_CHECK(ret, -1, "semctl");
  ret = semctl(semid, 0, GETVAL);
  printf("semval = %d\n", ret);
  struct sembuf P, V;
  P.sem_num = 0; // 下标
  P.sem_op = -1; // 对资源的影响
  P.sem_flg = SEM_UNDO;
  V.sem_num = 0; // 下标
  V.sem_op = 1;  // 对资源的影响
  V.sem_flg = SEM_UNDO;
  if (fork() == 0)
  { // 生产者-子
    while (1)
    {
      semop(semid, &P, 1);
      if (p[0] > 0)
      {

        printf("before produce, space = %d, goods = %d\n", p[0], p[1]);
        --p[0];
        ++p[1];
        printf("after produce, space = %d, goods = %d\n", p[0], p[1]);
      }
      semop(semid, &V, 1);
    }
  }
  else if (fork() == 0)
  { // 生产者 子->子
    while (1)
    {
      semop(semid, &P, 1);
      if (p[0] > 0)
      {

        printf("before produce, space = %d, goods = %d\n", p[0], p[1]);
        --p[0];
        ++p[1];
        printf("after produce, space = %d, goods = %d\n", p[0], p[1]);
      }
      semop(semid, &V, 1);
    }
  }
  else
  { // 父进程和第一个子进程并发执行，消费者
    while (1)
    {
      semop(semid, &P, 1);
      if (p[1] > 0)
      {

        printf("before consume, space = %d, goods = %d\n", p[0], p[1]);
        --p[1];
        ++p[0];
        printf("after consume, space = %d, goods = %d\n", p[0], p[1]);
      }
      semop(semid, &V, 1);
    }
    wait(NULL);
  }
  shmdt(p);
  shmctl(shmid, IPC_RMID, NULL);
}
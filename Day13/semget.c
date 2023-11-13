#include <learnCpp.h>
#define NUM 1000000
int main(void)
{
  key_t key = ftok("file1", 1);
  int shmid = shmget(key, 4096, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
  int *p = (int *)shmat(shmid, NULL, 0);
  ERROR_CHECK(p, (void *)-1, "shmat");
  p[0] = 0;
  int semid = semget(1000, 1, IPC_CREAT | 0600); // 创建一个信号量
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
  {
    for (int i = 0; i < NUM; i++)
    {
      semop(shmid, &P, 1);
      ++p[0];
      semop(shmid, &V, 1);
    }
  }
  else
  {
    for (int i = 0; i < NUM; i++)
    {
      semop(shmid, &P, 1);
      ++p[0];
      semop(shmid, &V, 1);
    }
    wait(NULL);
    printf("p[0] = %d\n", p[0]);
  }
  shmdt(p);
  shmctl(shmid, IPC_RMID, NULL);
}
#include <learnCpp.h>
int main(void)
{
  int semid = semget(1001, 2, IPC_CREAT | 0600);
  // key相同的信号量，长度必须相同
  ERROR_CHECK(semid, -1, "semget");
  // semctl(semid, 0, SETVAL, 10);
  // semctl(semid, 1, SETVAL, 10);
  unsigned short arr[2] = {10, 10};
  semctl(semid, 0, SETALL, arr);
  unsigned short retarr[2];
  semctl(semid, 0, GETALL, retarr);
  // printf("egg = %d, flour = %d\n", semctl(semid, 0, GETVAL), semctl(semid, 1, GETVAL));
  printf("egg = %d, flour = %d\n", retarr[0], retarr[1]);
  struct sembuf bread[2];
  bread[0].sem_num = 0;
  bread[0].sem_op = -3;
  bread[0].sem_flg = SEM_UNDO;
  bread[1].sem_num = 1;
  bread[1].sem_op = -2;
  bread[1].sem_flg = SEM_UNDO;
  struct sembuf cake[2];
  cake[0].sem_num = 0;
  cake[0].sem_op = -5;
  cake[0].sem_flg = SEM_UNDO;
  cake[1].sem_num = 1;
  cake[1].sem_op = -1;
  cake[1].sem_flg = SEM_UNDO;
  if (fork() == 0)
  {
    while (1)
    {
      printf("before make bread\n");
      printf("egg = %d, flour = %d\n", semctl(semid, 0, GETVAL), semctl(semid, 1, GETVAL));
      semop(semid, bread, 2); // 数组可以退化成指针；一个信号量影响两个资源
      printf("after make bread\n");
      printf("egg = %d, flour = %d\n", semctl(semid, 0, GETVAL), semctl(semid, 1, GETVAL));
      sleep(1);
    }
  }
  else
  {
    while (1)
    {
      printf("before make cake\n");
      printf("egg = %d, flour = %d\n", semctl(semid, 0, GETVAL), semctl(semid, 1, GETVAL));
      semop(semid, cake, 2); // 数组可以退化成指针；一个信号量影响两个资源
      printf("after make cake\n");
      printf("egg = %d, flour = %d\n", semctl(semid, 0, GETVAL), semctl(semid, 1, GETVAL));
      sleep(1);
    }
    wait(NULL);
  }
}
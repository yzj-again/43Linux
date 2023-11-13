#include <learnCpp.h>
int main(void)
{
  int shmid = shmget(1000, 4096, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
  void *ret = shmat(shmid, NULL, 0);
  ERROR_CHECK(ret, (void *)-1, "shmat");
  int iret = shmctl(shmid, IPC_RMID, NULL);
  ERROR_CHECK(iret, -1, "shmctl RMID");
  sleep(20);
  shmdt(ret); // 删除链接
}
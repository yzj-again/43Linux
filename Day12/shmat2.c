#include <learnCpp.h>
#define NUM 1000
int main(void)
{
  key_t key = ftok("file1", 1);
  int shmid = shmget(key, 4096, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
  int *p = (int *)shmat(shmid, NULL, 0);
  ERROR_CHECK(p, (void *)-1, "shmat");
  p[0] = 0;
  if (fork() == 0)
  {
    for (int i = 0; i < NUM; i++)
      ++p[0];
  }
  else
  {
    for (int i = 0; i < NUM; i++)
      ++p[0];
    wait(NULL);
    printf("p[0] = %d\n", p[0]);
  }
}
#include <learnCpp.h>
int main(void)
{
  key_t key = ftok("file1", 1);
  int shmid = shmget(key, 4096, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
  char *p = (char *)shmat(shmid, NULL, 0);
  ERROR_CHECK(p, (void *)-1, "shmat");
  // strcpy(p, "hello");
  for (int i = 0; i < 8; i++)
  {
    printf("p[%d] = %c\n", i, p[i]);
  }

  shmdt(p);
}
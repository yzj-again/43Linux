#include <learnCpp.h>
int main(void)
{
  // key_t key = ftok("file1", 1);
  int shmid = shmget(IPC_PRIVATE, 4096, IPC_CREAT | 0600);
  printf("shmid = %d\n", shmid);
  ERROR_CHECK(shmid, -1, "shmget");
  char *p = (char *)shmat(shmid, NULL, 0);
  ERROR_CHECK(p, (void *)-1, "shmat");
  if (fork() == 0)
  {
    sleep(1);
    printf("child p = %s\n", p);
  }
  else
  {
    strcpy(p, "hello");
    wait(NULL);
  }
}
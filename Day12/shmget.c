#include <learnCpp.h>
int main(void)
{

  key_t key = ftok("file1", 1);
  ERROR_CHECK(key, -1, "ftok");
  printf("key = %d\n", key);
  int shmid = shmget(key, 4096, IPC_CREAT | 0600);
  ERROR_CHECK(shmid, -1, "shmget");
}
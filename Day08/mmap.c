#include <learnCpp.h>
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 2);
  int fd = open(argv[1], O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  int ret = ftruncate(fd, 5);
  ERROR_CHECK(ret, -1, "ftruncate");
  char *p = (char *)mmap(NULL, 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  ERROR_CHECK(p, MAP_FAILED, "mmap");
  for (int i = 0; i < 5; i++)
  {
    printf("%c", p[i]);
  }
  printf("\n");
  *(p + 0) = 'H'; // 改掉了
  munmap(p, 5);
}
#include <learnCpp.h>
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 2);
  int oldfd = open(argv[1], O_RDWR);
  ERROR_CHECK(oldfd, -1, "open");
  printf("oldfd = %d\n", oldfd);
  int newfd = dup(oldfd);
  printf("newfd = %d\n", newfd);
  write(oldfd, "hello", 5);
  close(oldfd);
  write(newfd, " world", 6);
  // 结果是"hello world"
  // close(oldfd);
  close(newfd);
  // oldfd = 3
  // newfd = 4
  return 0;
}
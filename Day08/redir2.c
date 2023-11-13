#include <learnCpp.h>
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 2);
  int oldfd = open(argv[1], O_RDWR);
  printf("oldfd = %d\n", oldfd); // oldfd = 3
  ERROR_CHECK(oldfd, -1, "open");
  close(STDOUT_FILENO);
  int newfd = dup(oldfd);
  printf("oldfd = %d\n", oldfd); // oldfd = 3
  printf("newfd = %d\n", newfd); // newfd = 1
  return 0;
}
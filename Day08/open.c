#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./open file
  ARGS_CHECK(argc, 2);
  // int fd = open(argv[1], O_RDONLY);
  int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
  ERROR_CHECK(fd, -1, "open");
  printf("fd = %d\n", fd);
  close(fd);
  return 0;
}
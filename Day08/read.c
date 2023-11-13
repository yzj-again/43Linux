#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./read file
  ARGS_CHECK(argc, 2);
  // int fd = open(argv[1], O_RDONLY);
  int fd = open(argv[1], O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  printf("fd = %d\n", fd);
  // char buf[10] = {0};
  // ssize_t ret = read(fd, buf, sizeof(buf));
  // puts(buf);
  // 读一个二进制的数
  int i;
  read(fd, &i, sizeof(i));
  printf("i=%d\n", i); // i=1000000
  close(fd);
  return 0;
}
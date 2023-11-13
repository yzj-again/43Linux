#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./write file
  ARGS_CHECK(argc, 2);
  int fd = open(argv[1], O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  printf("fd = %d\n", fd);
  // ssize_t write(int __fd, const void *__buf, size_t __n)
  // char buf[10] = "hello"; // 这里如果是字符串，就是文本文件
  int i = 1000000;
  // printf("strlen(buf) = %ld\n", strlen(buf));
  write(fd, &i, sizeof(i));
  close(fd);
  return 0;
}
#include <learnCpp.h>
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 2);
  int fd = open(argv[1], O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  int ret = ftruncate(fd, 40960); // howareyouhowareyouho^@^@^@^@^@^@^@^@^@^@
  ERROR_CHECK(ret, -1, "frtuncate");
}
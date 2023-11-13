#include <learnCpp.h>
#include <sys/stat.h>  // typedef __mode_t mode_t; 只有mode_t 没有__mode_t
#include <sys/types.h> // __STD_TYPE __MODE_T_TYPE __mode_t;
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 3);
  // chmod(argv[2], argv[1]);
  mode_t mode;
  sscanf(argv[1], "%o", &mode);
  int ret = chmod(argv[2], mode);
  ERROR_CHECK(ret, -1, "chmod error");
  // drwxrwxr-x 2 zijianye zijianye  4096  8月 20 21:19 dir/
  // drwxrwxrwx 2 zijianye zijianye 4096 8月 20 21 : 19 dir /
  return 0;
}
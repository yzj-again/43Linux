#include <learnCpp.h>
#include <sys/stat.h>  // typedef __mode_t mode_t; 只有mode_t 没有__mode_t
#include <sys/types.h> // __STD_TYPE __MODE_T_TYPE __mode_t;
int main(int argc, char *argv[])
{
  // ./mkdir xxx
  ARGS_CHECK(argc, 2);
  mode_t mode = 0777;
  int ret = mkdir(argv[1], mode);
  ERROR_CHECK(ret, -1, "mkdir");
  return 0;
}
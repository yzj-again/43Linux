#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./rmdir xxx
  ARGS_CHECK(argc, 2);
  int ret = rmdir(argv[1]);
  ERROR_CHECK(ret, -1, "rmdir");
  return 0;
}
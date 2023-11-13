#include <learnCpp.h>
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 2);
  FILE *fp = fopen(argv[1], "r+");
  printf("fileno=%d\n", fp->_fileno);
  ERROR_CHECK(fp, NULL, "fopen");
  // int ret = write(3, "hello", 5); 3是魔法数，有意的符号，取代数字
  // 代码即注释
  // int ret = write(fp->_fileno, "hello", 5);
  int ret = write(fileno(fp), "hello", 5); // 面向接口编程
  ERROR_CHECK(ret, -1, "write");
  fclose(fp);
}
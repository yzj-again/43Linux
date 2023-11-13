#include <learnCpp.h>

#define PATH_MAX_LENGTH 1024
int main()
{
  char buf[PATH_MAX_LENGTH] = {0};
  char *ret = getcwd(buf, sizeof(buf));
  ERROR_CHECK(ret, NULL, "getcwd");
  printf("ret = %p, ret = %s\n", ret, ret); // ret = 0x7ffed8727db0, ret = /home/zijianye/43Linux/Day06/file
  printf("buf = %p, buf = %s\n", buf, buf); // buf = 0x7ffed8727db0, buf = /home/zijianye/43Linux/Day06/file
  // 报错：Numerical result out of range
  // 也可以写空指针
  printf("pwd = %s\n", getcwd(NULL, 0));
  // pwd = /home/zijianye/43Linux/Day06/file
  // getcwd返回指向堆空间的指针，要free
  return 0;
}

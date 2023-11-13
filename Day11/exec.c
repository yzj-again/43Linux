#include <learnCpp.h>
int main(void)
{

  printf("before exec!\n");
  // execl("add", "./add", "3", "4", NULL);
  char *argvVector[] = {"./add", "3", "4", NULL};
  execv("add", argvVector);
  printf("after exec!\n");
  return 0;
  // before exec!
  // lhs + rhs = 7
}
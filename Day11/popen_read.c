#include <learnCpp.h>
int main(void)
{
  printf("pid = %d\n", getpid());
  FILE *fp = popen("./print", "r");
  ERROR_CHECK(fp, NULL, "popen");
  char buf[1024] = {0};
  fread(buf, 1, sizeof(buf), fp);
  printf("message from pipe, buf = %s\n", buf);
}
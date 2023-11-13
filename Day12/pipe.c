#include <learnCpp.h>
int main(void)
{
  int pipefds[2];
  pipe(pipefds);
  printf("pipefds[0]= %d pipefds[1]=%d\n", pipefds[0], pipefds[1]); // 3 4
  write(pipefds[1], "hello", 5);
  char buf[1024] = {0};
  read(pipefds[0], buf, sizeof(buf));
  printf("msg from pipe = %s\n", buf);
}
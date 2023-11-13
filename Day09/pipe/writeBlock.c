#include <learnCpp.h>
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 2);
  int fdr = open(argv[1], O_RDWR);
  int fdw = open(argv[1], O_RDWR);
  puts("pipe open");
  char buf[4096];
  // int cnt = 0;
  // while (1)
  // {
  //   printf("cnt = %d\n", cnt++);
  //   write(fdw, buf, sizeof(buf)); // 17次
  // }
  fd_set rdset;
  fd_set wrset;
  int count = 0;
  while (1)
  {
    FD_ZERO(&rdset);
    FD_SET(fdr, &rdset);
    FD_ZERO(&wrset);
    FD_SET(fdw, &wrset);
    select(fdw + 1, &rdset, &wrset, NULL, NULL);
    if (FD_ISSET(fdr, &rdset))
    {
      printf("read count = %d\n", count++);
      read(fdr, buf, 2048);
    }
    if (FD_ISSET(fdw, &wrset))
    {
      printf("write count = %d\n", count++);
      write(fdw, buf, 4097);
    }
    // sleep(1);
  }
}
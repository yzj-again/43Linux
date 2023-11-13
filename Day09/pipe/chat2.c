#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./chat2 1.pipe 2.pipe
  ARGS_CHECK(argc, 3);
  // 1.交换顺序./chat2 1.pipe 2.pipe 先把1.pipe的写段打开
  int fdw = open(argv[1], O_WRONLY);
  int fdr = open(argv[2], O_RDONLY);
  puts("chat2 pipes open");
  char buf[4096] = {0};
  fd_set rdset; // 栈上
  while (1)
  {
    FD_ZERO(&rdset);
    FD_SET(STDIN_FILENO, &rdset);
    FD_SET(fdr, &rdset);
    select(fdr + 1, &rdset, NULL, NULL, NULL); // 陷入等待
    if (FD_ISSET(fdr, &rdset))
    {
      puts("msg from pipe");
      memset(buf, 0, sizeof(buf));
      int ret = read(fdr, buf, sizeof(buf));
      if (ret == 0)
      {
        printf("end!\n");
        break;
      }
      puts(buf);
    }
    if (FD_ISSET(STDIN_FILENO, &rdset))
    {
      puts("msg from stdin");
      memset(buf, 0, sizeof(buf));
      int ret = read(STDIN_FILENO, buf, sizeof(buf));
      printf("ret = %d\n", ret);
      if (ret == 0)
      {
        write(fdw, "nishigehaoren", 13);
        break;
      }
      write(fdw, buf, strlen(buf));
    }
  }
}
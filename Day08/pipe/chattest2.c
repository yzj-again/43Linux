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
  while (1)
  { // 管道有数据时是start12345xxxx
    printf("start");
    memset(buf, 0, sizeof(buf));
    printf("1");
    read(STDIN_FILENO, buf, sizeof(buf));
    printf("2");
    write(fdw, buf, strlen(buf)); // 执行后会被阻塞
    printf("3");
    memset(buf, 0, sizeof(buf));
    printf("4");
    read(fdr, buf, sizeof(buf));
    printf("5");
    puts(buf);
  }
}
#include <learnCpp.h>
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 2);
  int fdr = open(argv[1], O_RDONLY); // 会阻塞
  ERROR_CHECK(fdr, -1, "open");
  puts("pipe open!");
  char buf[10] = {0};
  read(fdr, buf, sizeof(buf));
  puts(buf);
  close(fdr);
}
#include <learnCpp.h>
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 2);
  int oldfd = open(argv[1], O_RDWR);
  ERROR_CHECK(oldfd, -1, "open");
  printf("You can see me!--1\n");
  printf("oldfd = %d\n", oldfd); // oldfd = 3
  int savefd = 5;
  // int dup2(int oldfd, int newfd); 将oldfd复制给newfd
  dup2(STDOUT_FILENO, savefd);
  printf("STDOUT_FILENO = %d", STDOUT_FILENO); // 1 输入到了file1里
  printf("savefd = %d", savefd);               // 5 输入到了file1里
  dup2(oldfd, STDOUT_FILENO);
  printf("You can`t see me!\n");
  dup2(savefd, STDOUT_FILENO);
  printf("You can see me!--2\n");
  return 0;
}
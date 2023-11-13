#include <learnCpp.h>
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 3);
  printf("argv[0] = %s", argv[0]);
  // argv[0] = ./add
  int lhs = atoi(argv[1]);
  int rhs = atoi(argv[2]);
  printf("lhs + rhs = %d\n", lhs + rhs);
  return 0;
}
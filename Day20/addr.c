#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./ip 192.168.14.9 1234 推荐1025-65535
  ARGS_CHECK(argc, 3);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET; // 表示使用的是IPV4
  addr.sin_port = htons(atoi(argv[2]));
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  printf("port = %x\n", addr.sin_port);
  printf("addr = %x\n", addr.sin_addr.s_addr);
  return 0;
}
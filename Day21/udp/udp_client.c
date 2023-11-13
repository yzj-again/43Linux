#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./udp_client 192.168.150.121 1234
  ARGS_CHECK(argc, 3)
  int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
  ERROR_CHECK(sockFd, -1, "socket");
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  int ret = sendto(sockFd, "hello udp", 9, 0, (struct sockaddr *)&addr, sizeof(addr));
  // 接收
  // 重新申请一个长度
  socklen_t sockLen = sizeof(addr);
  char buf[1024] = {0};
  ret = recvfrom(sockFd, buf, 1024, 0, (struct sockaddr *)&addr, &sockLen);
  ERROR_CHECK(ret, -1, "recvfrom");
  puts(buf);
  close(sockFd);
}
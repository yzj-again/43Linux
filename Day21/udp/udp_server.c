#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./udp_server 192.168.150.121 1234
  ARGS_CHECK(argc, 3)
  int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
  ERROR_CHECK(sockFd, -1, "socket");
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  int ret = bind(sockFd, (struct sockaddr *)&addr, sizeof(addr));
  ERROR_CHECK(ret, -1, "bind");
  struct sockaddr_in clientAddr;
  // 保存收到信息对方的地址
  socklen_t clientAddrLen = sizeof(clientAddr);
  char buf[1024] = {0};
  printf("%ud", clientAddrLen);
  ret = recvfrom(sockFd, buf, sizeof(buf), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
  ERROR_CHECK(ret, -1, "recvfrom");
  printf("buf = %s\n", buf);
  printf("client ip = %s\n", inet_ntoa(clientAddr.sin_addr));
  printf("client port = %d\n", ntohs(clientAddr.sin_port));
  // sendto 要放在recvfrom后面
  ret = sendto(sockFd, "nihao udp", 9, 0, (struct sockaddr *)&clientAddr, clientAddrLen);
  ERROR_CHECK(ret, -1, "sendto");
  return 0;
}
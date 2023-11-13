#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./server_chat 192.168.150.121 1234
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
  // 只是为了知道客户端地址信息
  ret = recvfrom(sockFd, buf, sizeof(buf), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
  ERROR_CHECK(ret, -1, "recvfrom");
  fd_set rdset;
  while (1)
  {
    FD_ZERO(&rdset);
    FD_SET(STDIN_FILENO, &rdset);
    FD_SET(sockFd, &rdset);
    select(sockFd + 1, &rdset, NULL, NULL, NULL);
    puts("select returns");
    if (FD_ISSET(STDIN_FILENO, &rdset))
    {
      memset(buf, 0, sizeof(buf));
      int ret = read(STDIN_FILENO, buf, sizeof(buf));
      if (ret == 0)
      {
        sendto(sockFd, buf, 0, 0, (struct sockaddr *)&clientAddr, clientAddrLen);
        break;
      }
      sendto(sockFd, buf, strlen(buf), 0, (struct sockaddr *)&clientAddr, clientAddrLen);
    }
    if (FD_ISSET(sockFd, &rdset))
    {
      memset(buf, 0, sizeof(buf));
      int ret = recvfrom(sockFd, buf, sizeof(buf), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
      // 之前是对面关闭管道，read/recv返回0
      // 发一个空的数据报
      if (ret == 0)
      {
        break;
      }
      puts(buf);
    }
  }
  close(sockFd);
  return 0;
}
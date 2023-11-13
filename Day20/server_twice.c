#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./listen 192.168.150.121 1234
  ARGS_CHECK(argc, 3);
  int socketFd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(socketFd, -1, "socket");
  printf("socketFd = %d\n", socketFd);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 创建时用sockaddr_in
  // 调用函数时，先取地址再强转
  // 对于bind而言，addr一定是本地地址，ip/127
  int ret = bind(socketFd, (struct sockaddr *)&addr, sizeof(addr));
  ERROR_CHECK(ret, -1, "bind");
  ret = listen(socketFd, 10);
  ERROR_CHECK(ret, -1, "listen");
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int netFd = accept(socketFd, (struct sockaddr *)&clientAddr, &clientAddrLen);
  ERROR_CHECK(netFd, -1, "accept");
  // printf("netFd = %d\n", netFd);
  // printf("client length = %d\n", clientAddrLen);
  // printf("client family = %d\n", clientAddr.sin_family);
  // printf("client port = %d\n", ntohs(clientAddr.sin_port));
  // printf("client ip = %s\n", inet_ntoa(clientAddr.sin_addr));
  // int netFd = accept(socketFd, NULL,NULL);
  send(netFd, "hello from server!", 18, 0);
  send(netFd, "hello", 5, 0);
  // 关闭与客户端的连接
  close(netFd);
  // 关闭服务器的监听套接字
  close(socketFd);
}
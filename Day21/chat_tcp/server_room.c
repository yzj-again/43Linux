#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./server 192.168.150.121 1234
  ARGS_CHECK(argc, 3)
  int sockFd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockFd, -1, "socket");
  int optval = 1;
  int ret = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));
  ERROR_CHECK(ret, -1, "setsockopt");
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  ret = bind(sockFd, (struct sockaddr *)&addr, sizeof(addr));
  ERROR_CHECK(ret, -1, "bind");
  ret = listen(sockFd, 10);
  ERROR_CHECK(ret, -1, "listen");
  // int netFd = accept(sockFd, NULL, NULL);
  // ERROR_CHECK(netFd, -1, "accept");
  fd_set rdset;      // 单纯的去保存就绪的fd
  fd_set monitorSet; // 使用一个单独的监听集合
  FD_ZERO(&monitorSet);
  FD_SET(STDIN_FILENO, &monitorSet);
  FD_SET(sockFd, &monitorSet);
  char buf[4096] = {0};
  int netFd[10] = {0};
  int currConnect = 0;
  // 服务端不在监听标准输入
  // 处理新的客户端连接：监听sockFd
  // 处理客户端发送的消息的转发：维护netFd的数组然后进行转发
  while (1)
  {
    // 将监听集合复制到reset
    memcpy(&rdset, &monitorSet, sizeof(fd_set));
    select(20, &rdset, NULL, NULL, NULL);
    // 监听和就绪都在一起
    // 管道一端关闭，另外一端读操作就绪，会一直就绪
    // 有新链接过来了
    if (FD_ISSET(sockFd, &rdset))
    {
      netFd[currConnect] = accept(sockFd, NULL, NULL);
      ERROR_CHECK(netFd[currConnect], -1, "accept");
      FD_SET(netFd[currConnect], &monitorSet); // 加入监听集合
      printf("new connect is accepted!current connect id is %d\n", currConnect);
      currConnect++;
    }
    for (int i = 0; i < currConnect; i++)
    {
      if (FD_ISSET(netFd[i], &rdset))
      {
        memset(buf, 0, sizeof(buf));
        recv(netFd[i], buf, sizeof(buf), 0);
        for (int j = 0; j < currConnect; j++)
        {
          if (j == i)
          {
            continue;
          }
          send(netFd[j], buf, strlen(buf), 0);
        }
      }
    }
  }
  close(sockFd);
}
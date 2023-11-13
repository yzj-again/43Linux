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
  int netFd = accept(sockFd, NULL, NULL);
  ERROR_CHECK(netFd, -1, "accept");
  // 建立监听集合
  fd_set rdset;
  char buf[4096] = {0};
  while (1)
  {
    FD_ZERO(&rdset);
    FD_SET(STDIN_FILENO, &rdset);
    FD_SET(netFd, &rdset);
    select(netFd + 1, &rdset, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &rdset))
    {
      memset(buf, 0, sizeof(buf));
      ret = read(STDIN_FILENO, buf, sizeof(buf));
      if (ret == 0)
      {
        send(netFd, "end", 3, 0);
        break;
      }
      send(netFd, buf, strlen(buf), 0);
    }
    // 管道一端关闭，另外一端读操作就绪，会一直就绪
    if (FD_ISSET(netFd, &rdset))
    {
      memset(buf, 0, sizeof(buf));
      ret = recv(netFd, buf, sizeof(buf), 0);
      if (ret == 0)
      {
        puts("chat is end!");
        break;
      }
      puts(buf);
    }
  }
  close(netFd);
  close(sockFd);
}
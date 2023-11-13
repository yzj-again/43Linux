#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./client 192.168.150.121 1234
  ARGS_CHECK(argc, 3)
  int sockFd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(sockFd, -1, "socket");
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  int ret = connect(sockFd, (struct sockaddr *)&addr, sizeof(addr));
  ERROR_CHECK(ret, -1, "connect");
  // 建立监听集合
  fd_set rdset;
  char buf[4096] = {0};
  while (1)
  {
    FD_ZERO(&rdset);
    FD_SET(STDIN_FILENO, &rdset);
    FD_SET(sockFd, &rdset);
    select(sockFd + 1, &rdset, NULL, NULL, NULL);
    if (FD_ISSET(STDIN_FILENO, &rdset))
    {
      memset(buf, 0, sizeof(buf));
      ret = read(STDIN_FILENO, buf, sizeof(buf));
      if (ret == 0)
      {
        send(sockFd, "end", 3, 0);
        break;
      }
      send(sockFd, buf, strlen(buf), 0);
    }
    if (FD_ISSET(sockFd, &rdset))
    {
      int lowat = 5;
      setsockopt(sockFd, SOL_SOCKET, SO_RCVLOWAT, &lowat, sizeof(lowat));
      memset(buf, 0, sizeof(buf));
      ret = recv(sockFd, buf, sizeof(buf), 0);
      if (ret == 0)
      {
        puts("chat is end!");
        break;
      }
      puts(buf);
    }
  }
  close(sockFd);
}
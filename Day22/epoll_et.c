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
  // 监听键盘输入和netFd
  int epfd = epoll_create(1);
  ERROR_CHECK(epfd, -1, "epoll_create");
  struct epoll_event event; // 设置文件描述符事件
  event.data.fd = STDIN_FILENO;
  event.events = EPOLLIN;
  epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event); // 把stdin以读事件加入监听
  event.data.fd = netFd;
  // event.events = EPOLLIN;
  event.events = EPOLLIN | EPOLLET;
  epoll_ctl(epfd, EPOLL_CTL_ADD, netFd, &event); // 把已连接socket以读事件加入监听
  char buf[5] = {0};
  struct epoll_event readyArr[2]; // 就绪事件队列
  while (1)
  {
    int readyNum = epoll_wait(epfd, readyArr, 2, -1); // epoll_wait的返回值是就绪事件队列的个数
    puts("epoll_wait returns");
    for (int i = 0; i < readyNum; i++)
    {
      if (readyArr[i].data.fd == STDIN_FILENO)
      {
        memset(buf, 0, sizeof(buf));
        int ret = read(STDIN_FILENO, buf, sizeof(buf) - 1);
        printf("stdin len = %d\n", ret);
        if (ret == 0)
        {
          goto end;
        }
        send(netFd, buf, strlen(buf), 0);
      }
      else if (readyArr[i].data.fd == netFd)
      {
        memset(buf, 0, sizeof(buf));
        // int ret = recv(netFd, buf, sizeof(buf) - 1, 0);
        // printf("netFd len = %d\n", ret);
        // if (ret == 0)
        // {
        //   goto end;
        // }
        int ret = 0;
        while (1)
        {
          memset(buf, 0, sizeof(buf));
          ret = recv(netFd, buf, sizeof(buf) - 1, MSG_DONTWAIT);
          puts(buf);
          if (ret == 0 || ret == -1)
          {
            break;
          }
        }

        // puts(buf);
      }
    }
  }
end:
  close(netFd);
  close(epfd);
  close(sockFd);
}
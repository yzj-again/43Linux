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
  // tcp的创建初始化连接
  int epfd = epoll_create(1); // set和zero
  struct epoll_event event;
  event.data.fd = sockFd;
  event.events = EPOLLIN;
  epoll_ctl(epfd, EPOLL_CTL_ADD, sockFd, &event); // 加入监听集合
  char buf[4096] = {0};
  int netFd[10] = {0};
  int currConnect = 0;
  struct epoll_event readyArr[11];
  while (1)
  {
    int readyNum = epoll_wait(epfd, readyArr, 11, -1); // 就绪事件队列长度
    puts("epoll_wait return");
    for (int i = 0; i < readyNum; i++)
    {
      // 遍历就绪事件队列-拿到就绪事件的文件描述符
      if (readyArr[i].data.fd == sockFd)
      {
        // 建立连接
        netFd[currConnect] = accept(sockFd, NULL, NULL);
        ERROR_CHECK(netFd[currConnect], -1, "accept");
        event.data.fd = netFd[currConnect];
        event.events = EPOLLIN;
        epoll_ctl(epfd, EPOLL_CTL_ADD, netFd[currConnect], &event);
        printf("new connect is accepted!current connect id is %d\n", currConnect);
        currConnect++;
      }
      else
      {
        memset(buf, 0, sizeof(buf));
        recv(readyArr[i].data.fd, buf, sizeof(buf), 0);
        for (int j = 0; j < currConnect; j++)
        {
          // 遍历到自己
          if (readyArr[i].data.fd == netFd[j])
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
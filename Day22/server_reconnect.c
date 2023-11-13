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
  int netFd = -1;
  // 监听键盘输入和netFd
  int epfd = epoll_create(1);
  ERROR_CHECK(epfd, -1, "epoll_create");
  struct epoll_event event; // 设置文件描述符事件
  event.data.fd = STDIN_FILENO;
  event.events = EPOLLIN;
  epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event); // 把stdin以读事件加入监听
  event.data.fd = sockFd;
  event.events = EPOLLIN;
  epoll_ctl(epfd, EPOLL_CTL_ADD, sockFd, &event); // 把监听socket加入监听
  char buf[4096] = {0};
  struct epoll_event readyArr[3]; // 就绪事件队列
  int isConnected = 0;
  time_t lastTime, newTime;
  while (1)
  {
    int readyNum = epoll_wait(epfd, readyArr, 3, 5000); // epoll_wait的返回值是就绪事件队列的个数
    puts("epoll_wait returns");
    // 5s后踢出客户端连接
    // 最开始没有客户端连接，用一个标记
    // 处于已连接状态且没有就绪队列为空
    if (readyNum == 0 && isConnected)
    {
      puts("time out!");
      newTime = time(NULL);
      if (newTime - lastTime > 5)
      {
        // out
        send(netFd, "free", 4, 0);
        close(netFd);
        event.data.fd = netFd;
        event.events = EPOLLIN;
        epoll_ctl(epfd, EPOLL_CTL_DEL, netFd, &event);
        isConnected = 0;
      }
    }
    for (int i = 0; i < readyNum; i++)
    {
      if (readyArr[i].data.fd == STDIN_FILENO)
      {
        if (!isConnected)
        {
          int ret = read(STDIN_FILENO, buf, sizeof(buf));
          if (ret == 0)
          {
            goto end;
          }
        }
        memset(buf, 0, sizeof(buf));
        int ret = read(STDIN_FILENO, buf, sizeof(buf));
        if (ret == 0)
        {
          goto end;
        }
        send(netFd, buf, strlen(buf), 0);
      }
      else if (readyArr[i].data.fd == sockFd)
      {
        if (isConnected)
        { // 不允许多个人连接
          int nofd = accept(sockFd, NULL, NULL);
          close(nofd);
          continue;
        }
        netFd = accept(sockFd, NULL, NULL);
        ERROR_CHECK(netFd, -1, "accept");
        // 将netFd加入监听事件队列
        event.data.fd = netFd;
        event.events = EPOLLIN;
        epoll_ctl(epfd, EPOLL_CTL_ADD, netFd, &event);
        isConnected = 1;
        lastTime = time(NULL);
      }
      else if (readyArr[i].data.fd == netFd)
      {
        memset(buf, 0, sizeof(buf));
        int ret = recv(netFd, buf, sizeof(buf), 0);
        // printf("ret=%d\n", ret);
        if (ret == 0)
        { // 客户端断开连接
          close(netFd);
          event.data.fd = netFd;
          event.events = EPOLLIN;
          epoll_ctl(epfd, EPOLL_CTL_DEL, netFd, &event);
          isConnected = 0;
        }
        // 每次发消息记录newTime
        lastTime = time(NULL);
        puts(buf);
      }
    }
  }
end:
  close(netFd);
  close(epfd);
  close(sockFd);
}
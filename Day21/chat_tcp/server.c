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
  // 希望程序一开始就阻塞在select
  // int netFd = accept(sockFd, NULL, NULL);
  // ERROR_CHECK(netFd, -1, "accept");
  // accpt要放在select后面
  // 去使用时要确保从标准输入中输入数据在客户端建立链接之后
  // 每次accept后要创建新的netFd，这个netFd加入监听
  // 分离监听和就绪
  // 如果客户端断开连接，服务端不要退出，要取消监听netFd
  // sockFd不需要取消监听，要保证客户端可以重新连接（accept->FD_SET）
  // 建立监听集合
  fd_set rdset;      // 单纯的去保存就绪的fd
  fd_set monitorSet; // 使用一个单独的监听集合
  FD_ZERO(&monitorSet);
  // 标准输入和sockFd加入监听集合monitorSet
  FD_SET(STDIN_FILENO, &monitorSet);
  FD_SET(sockFd, &monitorSet);
  char buf[4096] = {0};
  int netFd = -1;
  while (1)
  {
    // 将监听集合复制到reset
    memcpy(&rdset, &monitorSet, sizeof(fd_set));
    select(20, &rdset, NULL, NULL, NULL);
    // 不是sockFd+1而是monitorSet里最大的那个+1
    // 监听所有的监听文件描述符，找到其中就绪的文件描述符，把它填到rdset里
    // 之前监听就是就绪
    // 监听和就绪都在一起
    if (FD_ISSET(STDIN_FILENO, &rdset))
    {
      // if (netFd == -1)
      // {
      //   puts("no client is connected\n");
      //   break;
      // }
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
    // sockFd就绪，有新链接过来了，监听全连接队列，构建一个已连接socket
    if (FD_ISSET(sockFd, &rdset))
    {
      netFd = accept(sockFd, NULL, NULL);
      ERROR_CHECK(netFd, -1, "accept");
      FD_SET(netFd, &monitorSet); // 新的netFd加入监听集合
      // 如果只有一个rdset，每次循环会清空监听集合
      puts("new connect is accepted\n");
    }
    if (FD_ISSET(netFd, &rdset)) // 连接已经建立好，有可能过来数据
    {                            // 就绪事件多写一个
      memset(buf, 0, sizeof(buf));
      ret = read(netFd, buf, sizeof(buf));
      if (ret == 0)
      {
        puts("bye bye\n");
        // 不要break，客户端断开连接，不需要继续监听了
        FD_CLR(netFd, &monitorSet);
        close(netFd); // 关闭socket
        netFd = -1;
        continue;
      }
      puts(buf);
    }
  }
  close(sockFd);
}
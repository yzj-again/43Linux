#include <learnCpp.h>
int main()
{
  int epollFd = epoll_create(1); // 返回一个非负的文件描述符
  ERROR_CHECK(epollFd, -1, "epoll_create");
  printf("create epoll fd = %d\n", epollFd);
  close(epollFd);
  return 0;
}
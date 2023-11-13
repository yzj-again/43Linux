#include <learnCpp.h>
int epollAdd(int fd, int epollFd)
{
  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = fd;
  int ret = epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event);
  ERROR_CHECK(ret, -1, "epoll_ctl");
  return 0;
}
int epollDelete(int fd, int epollFd)
{
  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = fd;
  int ret = epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, &event);
  ERROR_CHECK(ret, -1, "epoll_ctl");
  return 0;
}
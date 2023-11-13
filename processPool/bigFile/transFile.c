#include <learnCpp.h>
#include "head.h"
int transFile(int netFd)
{
  // 打开一个文件
  int fd = open("file1", O_RDWR);
  ERROR_CHECK(fd, -1, "open");
  // int ret = send(netFd, "file1", 5, 0);
  // ERROR_CHECK(ret, -1, "send");
  train_t train;
  train.length = 5;
  strcpy(train.buf, "file1");
  int ret = send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);
  ERROR_CHECK(ret, -1, "send");
  while (1)
  {
    memset(&train, sizeof(train), 0);
    ret = read(fd, train.buf, sizeof(train.buf));
    ERROR_CHECK(ret, -1, "read");
    if (ret == 0)
    {
      break;
    }
    train.length = ret;
    ret = send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);
    ERROR_CHECK(ret, -1, "send");
  }
  train.length = 0;
  ret = send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);
  ERROR_CHECK(ret, -1, "send");
  close(fd);
}
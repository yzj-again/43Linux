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
  // 发送文件的大小
  struct stat statbuf;
  ret = fstat(fd, &statbuf);
  ERROR_CHECK(ret, -1, "fstat");
  train.length = 4;
  int fileSize = statbuf.st_size;
  memcpy(train.buf, &fileSize, sizeof(int));
  send(netFd, &train, train.length + sizeof(train.length), MSG_NOSIGNAL);
  ERROR_CHECK(ret, -1, "send");
  // 将文件对象数据发送到socket
  sendfile(netFd, fd, NULL, fileSize);
  //
  train.length = 0;
  ret = send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);
  ERROR_CHECK(ret, -1, "send");
  close(fd);
}
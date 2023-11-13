#include <learnCpp.h>
int main()
{
  int sockFd = socket(AF_INET, SOCK_STREAM, 0);
  int bufSize = 0;
  socklen_t len = sizeof(bufSize);
  // level 固定
  int ret = getsockopt(sockFd, SOL_SOCKET, SO_SNDBUF, &bufSize, &len);
  ERROR_CHECK(ret, -1, "getsockopt");
  printf("bufSize = %d, len = %d\n", bufSize, len);
  // bufSize = 16384, len = 4
  bufSize = 4096;
  ret = setsockopt(sockFd, SOL_SOCKET, SO_SNDBUF, &bufSize, len);
  ERROR_CHECK(ret, -1, "getsockopt");
  ret = getsockopt(sockFd, SOL_SOCKET, SO_SNDBUF, &bufSize, &len);
  ERROR_CHECK(ret, -1, "getsockopt");
  printf("bufSize = %d, len = %d\n", bufSize, len);
}
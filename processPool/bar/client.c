#include <learnCpp.h>
typedef struct train_s
{
  int length;
  char buf[1000];
} train_t;
int recvN(int sockFd, void *pstart, int len)
{
  int total = 0;
  int ret = 0;
  char *p = (char *)pstart;
  while (total < len)
  {
    ret = recv(sockFd, p + total, len - total, 0);
    total += ret;
  }
  return 0;
}
int recvFile(int sockFd)
{
  // 先获取文件名
  char name[1024] = {0};
  int dataLength = 0;
  // int ret = recv(sockFd, &dataLength, sizeof(int), 0); // ret是收到的字节数
  int ret = recvN(sockFd, &dataLength, sizeof(int));
  ERROR_CHECK(ret, -1, "recv");
  // ret = recv(sockFd, name, dataLength, 0);
  ret = recvN(sockFd, name, dataLength);
  ERROR_CHECK(ret, -1, "recv");
  int fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);
  ERROR_CHECK(fd, -1, "open");
  int fileSize;
  recvN(sockFd, &dataLength, sizeof(int)); // 头
  recvN(sockFd, &fileSize, dataLength);    // 车厢
  char buf[1024] = {0};
  // 进度条
  int downSize = 0;
  int lastSize = 0;
  int slice = fileSize / 10000;
  while (1)
  {
    // ret = recv(sockFd, &dataLength, sizeof(int), 0);
    ret = recvN(sockFd, &dataLength, sizeof(int));
    ERROR_CHECK(ret, -1, "recv");
    downSize += dataLength;
    if (downSize - lastSize > slice)
    {
      printf("%5.2lf%%\r", 100.0 * downSize / fileSize);
      // /r不不会刷新缓冲区
      fflush(stdout);
      lastSize = downSize;
    }
    if (dataLength == 0)
    {
      printf("100%%\n");
      break;
    }
    // ret = recv(sockFd, buf, dataLength, 0);
    ret = recvN(sockFd, buf, dataLength);
    ERROR_CHECK(ret, -1, "recv");
    // write(fd, buf, ret); // 收多少写多少，strlen()不计算0
    write(fd, buf, dataLength);
  }
}
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
  recvFile(sockFd);
  close(sockFd);
}
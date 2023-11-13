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
  time_t timeBegin, timeEnd;
  timeBegin = time(NULL);
  int pipefds[2];
  pipe(pipefds);
  int total = 0;
  while (total < fileSize)
  {
    int ret = splice(sockFd, NULL, pipefds[1], NULL, 4096, SPLICE_F_MORE);
    total += ret;
    splice(pipefds[0], NULL, fd, NULL, ret, SPLICE_F_MORE);
  }

  /*
  // 文件对象刚开始大小为0--客户端
  ftruncate(fd, fileSize);
  char *p = (char *)mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  ERROR_CHECK(p, MAP_FAILED, "mmap");
  // 直接放在p这里
  recvN(sockFd, p, fileSize);
  */
  recvN(sockFd, &dataLength, sizeof(int));
  timeEnd = time(NULL);
  printf("total time = %ld\n", timeEnd - timeBegin);
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
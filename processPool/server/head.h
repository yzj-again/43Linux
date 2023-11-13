int tcpInit(int *pSockFd, char *ip, char *port);
int sendFd(int pipeFd, int fdToSend, int exitFlag);
int recvFd(int pipeFd, int *pFdToRecv, int *pExitFlag);
int epollAdd(int fd, int epollFd);
int epollDelete(int fd, int epollFd);
int transFile(int netFd);
typedef struct train_s
{
  int length;
  char buf[1000];
} train_t;

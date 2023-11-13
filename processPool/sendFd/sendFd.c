#include <learnCpp.h>
int sendFd(int pipeFd, int fdToSend)
{
  struct msghdr hdr;
  memset(&hdr, 0, sizeof(hdr));
  // 第一个部分发送文本数据
  struct iovec iov[1]; // 长度为，离散数据退化成连续
  char buf[10] = "hello";
  iov[0].iov_base = buf;
  iov[0].iov_len = 5;
  hdr.msg_iov = iov;
  hdr.msg_iovlen = 1;
  // 第二个部分发送控制信息
  struct cmsghdr *pcmsghdr = (struct cmsghdr *)calloc(1, sizeof(struct cmsghdr));
  pcmsghdr->cmsg_len = CMSG_LEN(sizeof(int)); // 要承载的控制信息是一个整型数据
  pcmsghdr->cmsg_level = SOL_SOCKET;
  pcmsghdr->cmsg_type = SCM_RIGHTS;
  *(int *)CMSG_DATA(pcmsghdr) = fdToSend;
  hdr.msg_control = pcmsghdr;
  hdr.msg_controllen = CMSG_LEN(sizeof(int));
  int ret = sendmsg(pipeFd, &hdr, 0);
  ERROR_CHECK(ret, -1, "sendmsg");
  return 0;
}
int recvFd(int pipeFd, int *pFdToRecv)
{
  struct msghdr hdr;
  memset(&hdr, 0, sizeof(hdr));
  // 第一个部分发送文本数据
  struct iovec iov[1]; // 长度为，离散数据退化成连续
  char buf[10] = {0};
  iov[0].iov_base = buf;
  iov[0].iov_len = sizeof(buf); // 无论什么情况不要写0
  hdr.msg_iov = iov;
  hdr.msg_iovlen = 1;
  // 第二个部分发送控制信息
  struct cmsghdr *pcmsghdr = (struct cmsghdr *)calloc(1, sizeof(struct cmsghdr));
  pcmsghdr->cmsg_len = CMSG_LEN(sizeof(int)); // 要承载的控制信息是一个整型数据
  pcmsghdr->cmsg_level = SOL_SOCKET;
  pcmsghdr->cmsg_type = SCM_RIGHTS;
  hdr.msg_control = pcmsghdr;
  hdr.msg_controllen = CMSG_LEN(sizeof(int));
  int ret = recvmsg(pipeFd, &hdr, 0);
  ERROR_CHECK(ret, -1, "recvmsg");
  // 收完以后再改掉
  *pFdToRecv = *(int *)CMSG_DATA(pcmsghdr);
  return 0;
}
int main()
{
  int sv[2];
  socketpair(AF_LOCAL, SOCK_STREAM, 0, sv);
  if (fork() == 0)
  { // 子
    // close(sv[0]); // 关闭一条管道
    int fd = open("file", O_RDWR);
    printf("child fd = %d\n", fd);
    write(fd, "hello", fd);
    sendFd(sv[1], fd);
    sleep(10);
    exit(0);
  }
  else
  {
    // 不使用sendFd，父子进程fd相同，但不是同一个文件对象
    // c=5 p=5 -->c=5, p=6
    // close(sv[1]);
    int fd = open("file1", O_RDWR);
    printf("parent fd = %d\n", fd);
    int newFd;
    recvFd(sv[0], &newFd);
    printf("new fd = %d\n", newFd);
    write(newFd, "world", 5);
    // 子进程sendFd把open出来的文件对象发给了父进程
    // 父进程拿到了子进程的fd,在数值上和子进程的fd不相同
    // 但是文件对象是一样的，共享文件对象
    wait(NULL);
  }
}
#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./connect 192.168.14.9 1234
  ARGS_CHECK(argc, 3);
  int socketFd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(socketFd, -1, "socket");
  printf("socketFd = %d\n", socketFd);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  // 创建时用sockaddr_in
  // 调用函数时，先取地址再强转
  int ret = connect(socketFd, (struct sockaddr *)&addr, sizeof(addr));
  // 第一次握手
  // 192.168.150.121.33306 > 192.168.150.121.1234
  // 22:52:53.709838 IP 192.168.150.121.33306 > 192.168.150.121.1234: Flags [S], seq 2394641661, win 65495, options [mss 65495,sackOK,TS val 2271245425 ecr 0,nop,wscale 7], length 0
  // 22:52:53.709847 IP 192.168.150.121.1234 > 192.168.150.121.33306: Flags [R.], seq 0, ack 2394641662, win 0, length 0
  ERROR_CHECK(ret, -1, "connect");
  char buf[1024] = {0};
  ret = recv(socketFd, buf, sizeof(buf), 0);
  ERROR_CHECK(ret, -1, "recv");
  puts(buf);
  // ret = send(socketFd, "nihao!", 6, 0);
  ERROR_CHECK(ret, -1, "send");
  close(socketFd);
}
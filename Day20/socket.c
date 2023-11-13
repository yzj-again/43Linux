#include <learnCpp.h>
int main(void)
{
  int socketFd = socket(AF_INET, SOCK_STREAM, 0);
  ERROR_CHECK(socketFd, -1, "socket");
  printf("socketFd = %d\n", socketFd);
  close(socketFd);
}
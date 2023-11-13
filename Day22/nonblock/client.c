#include <learnCpp.h>
int main(int argc, char *argv[])
{
    // ./server 192.168.14.9 1234
    ARGS_CHECK(argc, 3);
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    // 创建一个socket 支持IPv4和TCP
    ERROR_CHECK(sockFd, -1, "socket");
    printf("sockFd = %d\n", sockFd);
    struct sockaddr_in addr; // 创建时 用 sockaddr_in
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(sockFd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");
    // sleep(10);
    send(sockFd, "hello", 5, 0);
    sleep(10);
    close(sockFd);
}
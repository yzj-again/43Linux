#include <learnCpp.h>
int setNonblock(int fd)
{
    int status = fcntl(fd, F_GETFL); // 获取状态
    status |= O_NONBLOCK;            // 既要原来的属性也要O_NONBLOCK
    int ret = fcntl(fd, F_SETFL, status);
    ERROR_CHECK(ret, -1, "fcntl");
    return 0;
}
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
    // 调用函数时，先取地址再强转
    // 对于bind而言 addr一定是本地地址
    int ret = bind(sockFd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");
    ret = listen(sockFd, 10);
    ERROR_CHECK(ret, -1, "listen");
    struct sockaddr_in clientAddr;
    // socklen_t clientAddrLen = /*sizeof(clientAddr)*/ 0;//写0是会出问题
    socklen_t clientAddrLen = sizeof(clientAddr); // 写0是会出问题
    int netFd = accept(sockFd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    ERROR_CHECK(netFd, -1, "accept");
    printf("netFd = %d\n", netFd);
    printf("client addr length = %d\n", clientAddrLen);
    printf("client family = %d\n", clientAddr.sin_family);
    printf("client port = %d\n", ntohs(clientAddr.sin_port));
    printf("client ip = %s\n", inet_ntoa(clientAddr.sin_addr));
    char buf[4096] = {0};
    // //setNonblock(netFd);
    // ret = recv(netFd,buf,sizeof(buf),MSG_DONTWAIT);
    // if(ret == -1){
    //     puts("no resource now!\n");
    // }
    // ret = recv(netFd,buf,sizeof(buf),0);
    // if(ret == -1){
    //     puts("no resource now!\n");
    // }
    // //ERROR_CHECK(ret,-1,"recv");
    // // while(1){
    // //     ret = recv(netFd,buf,sizeof(buf),MSG_DONTWAIT);
    // //     //临时让本次recv是非阻塞的
    // //     if(ret == -1){
    // //         puts("no resource now!\n");
    // //         sleep(1);
    // //     }
    // //     else{
    // //         break;
    // //     }
    // // }
    bzero(buf, sizeof(buf));
    ret = recv(netFd, buf, sizeof(buf), MSG_PEEK);
    puts(buf);
    bzero(buf, sizeof(buf));
    ret = recv(netFd, buf, sizeof(buf), 0);
    puts(buf);
    close(sockFd);
}
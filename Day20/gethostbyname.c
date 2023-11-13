#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./gethostbyname www.baidu.com
  ARGS_CHECK(argc, 2);
  struct hostent *pHost = gethostbyname(argv[1]);
  // 处理报错 不能使用perror
  if (pHost == NULL)
  {
    fprintf(stderr, "gethostbyname:%s\n", strerror(h_errno));
    // strerror根据报错信息，返回具体内容
    return -1;
  }
  printf("host real name = %s\n", pHost->h_name);
  for (int i = 0; pHost->h_aliases[i] != NULL; i++)
  {
    printf("host aliases[%d] = %s\n", i, pHost->h_aliases[i]);
  }
  printf("addrtype = %d\n", pHost->h_addrtype);
  printf("addrLength = %d\n", pHost->h_length);
  for (int i = 0; pHost->h_addr_list[i] != NULL; i++)
  {
    char buf[1024] = {0};
    inet_ntop(pHost->h_addrtype, pHost->h_addr_list[i], buf, sizeof(buf));
    printf("addr =%s\n", buf);
  }
  // host real name = www.a.shifen.com
  // host aliases[0] = www.baidu.com
  // addrtype = 2
  // addrLength = 4
  // addr =14.119.104.189
  // addr =14.119.104.254
  return 0;
}
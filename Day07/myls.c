#include <learnCpp.h>
int main(int argc, char *argv[])
{
  // ./myls dir
  ARGS_CHECK(argc, 2);
  DIR *dirp = opendir(argv[1]);
  ERROR_CHECK(dirp, NULL, "opendir");
  struct dirent *pdirent;
  struct stat statbuf; // 主调函数分配
  while ((pdirent = readdir(dirp)) != NULL)
  {
    int ret = stat(pdirent->d_name, &statbuf);
    ERROR_CHECK(ret, -1, "stat");
    printf("%x ,%ld ,%s ,%s ,%8ld ,%s ,%s\n",
           statbuf.st_mode,  // 81b4 ->1000 0001 1011 0100   -rw-rw-r-- -> 0001 1011 0100  100664 ->1,000 000,1 10,11 0,100
           statbuf.st_nlink, // 41fd ->0100 0001 1111 1101   drwxrwxr-x -> 0001 1111 1101  40775  ->0,100 000,1 11,11 1,101
           // statbuf.st_uid,
           getpwuid(statbuf.st_uid)->pw_name,
           // statbuf.st_gid,
           getgrgid(statbuf.st_gid)->gr_name,
           statbuf.st_size,
           ctime(&(statbuf.st_mtime)), // 格式不方便调整
           pdirent->d_name);
  }
  closedir(dirp);
  return 0;
}
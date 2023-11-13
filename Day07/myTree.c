#include <learnCpp.h>
int DFSprint(char *path, int width);
int main(int argc, char *argv[])
{
  ARGS_CHECK(argc, 2);
  puts(argv[1]);
  DFSprint(argv[1], 4);
  return 0;
}

int DFSprint(char *path, int width)
{
  DIR *dirp = opendir(path);
  ERROR_CHECK(dirp, NULL, "opendir");
  struct dirent *pdirent;
  char newPath[1024] = {0};
  while ((pdirent = readdir(dirp)) != NULL)
  {
    /* code */
    if (strcmp(pdirent->d_name, ".") == 0 ||
        strcmp(pdirent->d_name, "..") == 0)
    {
      continue;
    }
    printf("|");
    for (int i = 1; i < width; i++)
    {
      printf("─");
    }

    puts(pdirent->d_name);
    if (pdirent->d_type == DT_DIR)
    {
      // 拼接
      sprintf(newPath, "%s%s%s", path, "/", pdirent->d_name);
      DFSprint(newPath, width + 4);
    }
  }
}
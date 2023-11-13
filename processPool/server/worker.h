#include <learnCpp.h>
enum
{
  FREE,
  BUSY
};
typedef struct workerData_s
{
  pid_t pid;
  int status;
  // 保存管道的pipeFd
  int pipeFd;
} workerData_t;
int makeChild(workerData_t *workerArr, int workerNum);
int eventHandler(int pipeFd);
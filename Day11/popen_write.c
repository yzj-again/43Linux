#include <learnCpp.h>
int main(void)
{
  FILE *fp = popen("./sub", "w");
  ERROR_CHECK(fp, NULL, "popen");
  fwrite("1000x 999", 1, 8, fp);
  return 0;
}
#include <stdio.h>

void modifyPointer(int *ptr)
{
  printf("fun before ptr=%p\n", ptr);
  // int value = 42;
  //  ptr = &value; // 不可行
  *ptr = 2; // 可行
  printf("fun after ptr=%p\n", ptr);
}

int main()
{
  int a = 1;
  int *ptr = &a;
  printf("main before ptr=%p\n", ptr);
  modifyPointer(ptr);
  printf("main after ptr=%p\n", ptr);
  printf("a = %d\n", a);
  if (ptr == NULL)
  {
    printf("Received a null pointer in main function.\n");
  }
  else
  {
    printf("Received a non-null pointer in main function.\n");
  }

  return 0;
}
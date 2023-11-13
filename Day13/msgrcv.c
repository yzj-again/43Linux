#include <learnCpp.h>

typedef struct msgbuf
{
  long mtype;
  char mtext[256];
} myMsg_t;

int main(void)
{
  int msgid = msgget(1000, IPC_CREAT | 0600);
  ERROR_CHECK(msgid, -1, "msgget");
  long type;
  printf("who are you?\n");
  scanf("%ld", &type);
  myMsg_t msg;
  memset(&msg, 0, sizeof(msg));
  msgrcv(msgid, &msg, sizeof(msg.mtext), type, 0);
  printf("you are %ld, msg = %s\n", msg.mtype, msg.mtext);
}
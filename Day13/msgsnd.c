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
  myMsg_t msg1;
  myMsg_t msg2;
  myMsg_t msg3;
  msg1.mtype = 1;
  strcpy(msg1.mtext, "你好msg2");
  msg2.mtype = 2;
  strcpy(msg2.mtext, "你好msg3");
  msg3.mtype = 3;
  strcpy(msg3.mtext, "你好msg1");
  // 发
  msgsnd(msgid, &msg1, strlen(msg1.mtext), 0);
  msgsnd(msgid, &msg2, strlen(msg2.mtext), 0);
  msgsnd(msgid, &msg3, strlen(msg3.mtext), 0);
}
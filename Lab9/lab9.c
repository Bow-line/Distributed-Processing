#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE     128

typedef struct msgbuf
{
    long    mtype;
    char    mtext[MAXSIZE];
}msgbuf;

int main()
{
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    struct msgbuf sbuf;
    size_t buflen;

    key = 1234;

    if ((msqid = msgget(key, msgflg )) < 0)
    {
        perror("msgsnd");
        exit(1);
    }

    //Message Type
    sbuf.mtype = 1;

    printf("Enter a message:");
    scanf("%[^\n]",sbuf.mtext);
    getchar();

    buflen = strlen(sbuf.mtext) + 1 ;

    if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
    {
        printf ("Error while seding a message");
        perror("msgsnd");
        exit(1);
    }

    else
        printf("Message Sent\n");

    exit(0);
}

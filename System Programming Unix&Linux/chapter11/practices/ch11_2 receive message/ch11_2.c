#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>

struct mymsgbuf {
	long mtype;
	char mtext[80];
};

int main(){
	struct mymsgbuf inmsg;
	key_t key;
	int msgid, len;

	key = ftok("keyfile", 1);
	if((msgid = msgget(key, 0)) < 0){ // msgget()의 두번째 인자를 0으로 지정: 기존 메시지 큐의 식별자를 리턴.
		perror("msgget");
		exit(1);
	}

	len = msgrcv(msgid, &inmsg, 80, 0, 0);
	printf("Recevied MSG = %s, len=%d\n", inmsg.mtext, len);
}

/*
# ipcs -q
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0xffffffff 1          dj         644        80           1       

# ./a.out
# ipcs -q  // messages turned to 0 from 1
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0xffffffff 1          dj         644        0            0     

*/
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf {
	long mtype;
	char mtext[80];
};

int main() {
	key_t key;
	int msgid;
	struct mymsgbuf mesg;

	// returns a key base don path and id that is usable in subsequent calls to msget(), semget(), shmget()
	// returns the same key value for all paths that name the same file, when called with the same id value.
	key = ftok("keyfile", 1);

	msgid = msgget(key, IPC_CREAT | 0644); // 새로운 키면 식별자 새로 생성.
	if(msgid == -1){
		perror("msgget");
		exit(1);
	}

	mesg.mtype = 1;
	strcpy(mesg.mtext, "Message Q Test");

	// IPC_NOWAIT: 메시지 큐가 가득 찬 경우, 기다리지 않고 바로 오류를 리턴.
	if(msgsnd(msgid, (void*) &mesg, 80, IPC_NOWAIT) == -1){
		perror("msgsnd");
		exit(1);
	}

}
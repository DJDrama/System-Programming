#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf {
	long type;
	char text[128];
};

int main(){
	key_t key;
	int msgid;
	struct mymsgbuf msg;
	char input[128];

	key = ftok("keyfile", 1);
	msgid = msgget(key, IPC_CREAT | 0644);
	if(msgid==-1){
		perror("msgget");
		exit(1);
	}

	printf("To Server: ");
	fgets(input, sizeof(input), stdin);

	msg.type = 1;
	strcpy(msg.text, input);

	if(msgsnd(msgid, (void *) &msg, sizeof(msg.text), 0) == -1){
		perror("msgsnd");
		exit(1);
	}

	msgrcv(msgid, &msg, sizeof(msg.text), 2, 0);
	printf("From Server: %s\n", msg.text);
}
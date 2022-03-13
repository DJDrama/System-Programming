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

	msgrcv(msgid, &msg, sizeof(msg.text), 1, 0);
	printf("From Client: %s\n", msg.text);

	printf("To Client: ");
	fgets(input, sizeof(input), stdin);

	msg.type=2;
	strcpy(msg.text, input);

	if(msgsnd(msgid, (void *) &msg, sizeof(msg.text), 0) == -1){
		perror("msgsnd");
		exit(1);
	}
}
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	key_t key;
	int msgid;

	key = ftok("keyfile", 1);
	msgid = msgget(key, IPC_CREAT | 0644);
	if(msgid == -1){
		perror("msgget");
		exit(1);
	}

	printf("Before IPC_RMID\n");
	system("ipcs -q");
	msgctl(msgid, IPC_RMID, (struct msqid_ds *) NULL);
	printf("After IPC_RMID\n");
	system("ipcs -q");
}

/*
$ ./a.out 
Before IPC_RMID

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0xffffffff 1          dj         644        0            0           

After IPC_RMID

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages  
*/
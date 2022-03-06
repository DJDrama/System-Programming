#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	key_t key;
	int shmid;

	key = ftok("shmfile", 1);
	shmid = shmget(key, 1024, IPC_CREAT|0644);
	if(shmid==-1){
		perror("shmget");
		exit(1);
	}
}
/*
> ipcs -m
IPC status from <running system> as of Sun Mar  6 22:52:57 KST 2022
T     ID     KEY        MODE       OWNER    GROUP
Shared Memory:
m  65536 0xffffffff --rw-r--r--       dj    staff
*/
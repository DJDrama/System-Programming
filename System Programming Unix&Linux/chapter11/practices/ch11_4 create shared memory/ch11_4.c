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
------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status   
0xffffffff 11337751   dj           644        1024       0                  

nattch=0 : No process that hs been connected to this shared memory yet.
*/
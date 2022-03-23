#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	pid_t pid;

	switch(pid = fork()){
		case -1: 
			perror("fork");
			exit(1);
			break;
		case 0:
			printf("Child Process - My PID: %d, My Parent's PID: %d\n", (int) getpid(), (int) getppid());
			break;
		default : 
			printf("Parent Process = My PID: %d, My Parent's PID: %d, My Child's PID: %d\n", (int) getpid(), (int) getppid(), (int) pid);
			break;
	}
	printf("End of fork\n");
}
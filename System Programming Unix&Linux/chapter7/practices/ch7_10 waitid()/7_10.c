#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int status;
	pid_t pid;
	siginfo_t infop;

	if((pid=fork()) <0){
		perror("fork");
		exit(1);
	}

	if(pid==0){
		printf("--> Child Process\n");
		sleep(2);
		exit(2);
	}

	printf("--> Parent Process\n");

	// P_PID: pid가 id 와 일치하는 자식 프로세스를 기다린다
	// WEXITED: 자식 프로세스가 종료될 때까지 기다린다.
	while(waitid(P_PID, pid, &infop, WEXITED)!=0){
		printf("Parent still wait...\n");
	}

	printf("Child's PID: %d\n", infop.si_pid);
	printf("Child's UID: %d\n", infop.si_uid);
	printf("Child's Exit Reason Code: %d\n", infop.si_code); // 자식 프로세스가 종료된 이유 코드
	printf("Child's Exit Status: %d\n", infop.si_status); // 자식 프로세스의 종료 상태값
}

/*
--> Parent Process
--> Child Process
Child's PID: 48141
Child's UID: 0
Child's Exit Reason Code: 1
Child's Exit Status: 2
*/
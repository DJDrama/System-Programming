#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int status;
	pid_t pid;
	switch(pid = fork()){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			printf("--> Child Process\n");
			exit(2); // 종료 상탯값: 2
			break;
		default:
			while(wait(&status) != pid)
				continue;
			printf("--> Parent process\n");
			printf("Status: %d, %x\n", status, status);
			printf("Child Process Exit Status:%d\n", status >> 8); // 자식 프로세스가 전달한 값은 부모 프로세스에 왼쪽으로 한 바이트 이동해 전달되므로 오른쪽으로 1바이트(8비트) 이동시켜야 함
			break;
	}
}

/*
--> Child Process
--> Parent process
Status: 512, 200
Child Process Exit Status:2
*/
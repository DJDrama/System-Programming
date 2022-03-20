#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

	pid_t pid;
	pid = fork();

	if(pid>0)
		printf("I am the parent of pid=%d\n", pid);
	else if(!pid)
		printf("I am the child!\n");
	else
		perror("fork");
}

/*
I am the parent of pid=76499
I am the child!
*/
#include <unistd.h>
#include <stdio.h>

int main(){
	printf("PID: %d\n", (int) getpid());
	printf("PPID: %d\n", (int) getppid());
}

/*
PID: 48257
PPID: 47770
*/
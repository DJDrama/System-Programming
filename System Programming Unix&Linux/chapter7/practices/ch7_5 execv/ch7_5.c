#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	char *argv[3];

	printf("Before exec function\n");

	argv[0] = "ls";
	argv[1] = "-a";
	argv[2] = NULL;

	if(execv("/usr/bin/ls", argv) == -1){ // Only in linux (cannot find in Mac)
		perror("execv");
		exit(1);
	}

	printf("After exec function\n");
}

/*
$ ./a.out 
Before exec function
.  ..  a.out  ch7_5.c
*/
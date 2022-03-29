#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("--> Before execvp function\n");
	char *argv[3];
	argv[0] = "ls";
	argv[1] = "-a";
	argv[2] = NULL;
	setuid(0);
	if(execvp("ls", argv) == -1){
		perror("execvp");
		exit(1);
	}
	
	printf("--> After execvp function\n"); // This line should not be printed.
}
	
	
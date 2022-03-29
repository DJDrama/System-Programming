#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("--> Before execlp function\n");
	setuid(0);
	if(execlp("ls", "ls", "-a", (char*) NULL) == -1){
		perror("execlp");
		exit(1);
	}
	
	printf("--> After execlp function\n"); // This line should not be printed.
}
	
	
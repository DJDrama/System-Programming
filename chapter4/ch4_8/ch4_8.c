#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int fd;
	
	fd = open("tmp.bbb", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd==-1){
		perror("Open");
		exit(1);
	}
	
	int n;
	n = dup2(fd, 1); // set fd to 1
	printf("DUP2: Standard Output Redirection(%d)\n", n);
	
	n=dup2(fd, 10); //set fd to 10
	printf("DUP2: set fd to %d\n", n);
	close(fd);
}

/* ./a.out --> tmp.bbb is created with write mode
* cat tmp.bbb --> DUP2: Standard Output Redirection(1)\n DUP2: set fd to 10\n
*/
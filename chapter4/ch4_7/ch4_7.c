#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int fd, fd1;
	
	fd = open("tmp.aaa", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd==-1){
		perror("Creat tmp.aaa");
		exit(1);
	}
	close(1); // close file descriptor 1
	printf("DUP FD=%d\n", fd);  // fd=3 (number next to 2, since 0, 1, 2 is already taken)
	fd1 = dup(fd); // new file descriptor is set
	printf("DUP FD1=%d\n", fd1); // since 1 is closed, fd1 would take file descriptor 1
	printf("Standard Output Redirection\n");
	
	close(fd);
}

/* ./a.out
* cat tmp.aaa --> DUP FD=1\n Standard Output Redirection
*/
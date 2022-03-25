#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int fd, n;

	fd = open("travel_wallet.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644); 
	
	if(fd==-1){
		perror("open");
		return -1;
	}
	
	if(fcntl(fd, F_SETFD, FD_CLOEXEC) == -1){
		perror("fcntl");
		return -1;
	}
	
	if(execl("exec_file", "./exec_file", NULL) == -1){
		perror("execl");
		return -1;
	}
	
	printf("End of fcntl_example\n");
	
	close(fd);
	return 0;
}



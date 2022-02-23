#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int fd, flags;
	fd = open("linux.txt", O_RDWR); // read and write
	if(fd==-1){
		perror("Open");
		exit(1);
	}
	
	if((flags = fcntl(fd, F_GETFL)) == -1){  // F_GETFL = get flag info
		perror("fcntl");
		exit(1);
	}
	
	flags |= O_APPEND;
	
	if(fcntl(fd, F_SETFL, flags) == -1){ // set new flag
		perror("fcntl");
		exit(1);
	}
	
	if(write(fd, "Hanbit Academy\n", 15) !=15)
		perror("write");
	
	close(fd);
}

/* ./a.out 
*  --> Linux System Programming\nHanbit Academy
*/
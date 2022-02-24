#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int fd, n;
	char buf[10];
	
	fd = open("linux.txt", O_RDONLY); // READ_ONLY
	if(fd==-1){
		perror("Open");
		exit(1);
	}
	
	n = read(fd, buf, 5);
	if(n==-1){
		perror("Read");
		exit(1);
	}
	
	buf[n]='\0';  // (0~4 : Linux, 5: \n)
	printf("n=%d, buf=%s\n", n, buf);
	close(fd);
}

/*
* ./a.out --> Open: No such file or directory
* vi linux.txt --> Linux System Programming
* cat linux.txt --> Linux System Programming
* ./a.out --> n=5, buf=Linux\n  
*/
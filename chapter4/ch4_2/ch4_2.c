#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int fd;
	fd = open("test.txt", O_CREAT | O_EXCL, 0644); // O_EXCL : error if file exists
	if(fd==-1){
		perror("Excl");
		exit(1);
	}
	close(fd);
}

/**
* ls test.txt --> No such file or directory
* ./a.out
* ls test.txt --> test.txt
* ./a.out --> Excl: File exists
*/
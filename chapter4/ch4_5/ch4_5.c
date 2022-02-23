#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int rfd, wfd, n;
	char buf[10];
	
	rfd = open("linux.txt", O_RDONLY);
	if(rfd==-1){
		perror("Open");
		exit(1);
	}
	
	wfd = open("linux.bak", O_CREAT | O_WRONLY | O_TRUNC, 0644); // CREAT with Write Only, and if exists, truncate file, making length to 0
	if(wfd == -1){
		perror("Open linux.bak");
		exit(1);
	}
	
	while((n=read(rfd, buf, 6)) > 0) { // read 6 bytes
		if(write(wfd, buf, n)!=n) // write should be (n=6) and must be equal to (n=6)
			perror("Write");
	}
	
	if(n==-1)
		perror("Read");
	
	close(rfd);
	close(wfd);
}

/* ./a.out --> Open: No such file or directory
* vi linux.txt --> Linux System Programming
* ./a.out
* ls --> a.out ch4_5.c linux.bak linux.txt
* cat linux.bak --> Linux System Programming
*/
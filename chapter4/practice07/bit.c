#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int arg, char *argv[]){
	int rfd, wfd, n;
	char buf[BUFSIZ];
	
	rfd = open(argv[1], O_RDONLY);
	if(rfd==-1){
		perror("Open");
		exit(1);
	}
	
	wfd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(wfd==-1){
		perror("Open argv[2]");
		exit(1);
	}
	
	if((n=read(rfd, buf, BUFSIZ)) > 0){
		if(write(wfd, buf, n)!=n)
			perror("Write");
	}
	if(n==-1)
		perror("Read");
	
	close(rfd);
	close(wfd);
	
}
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

/* ./newcp han.c bit.c
* cat bit.c --> copied!
* ls
* -rw-r--r-- 1 dj dj   571  2월 24 00:22 bit.c
* -rw-rw-r-- 1 dj dj   626  2월 24 00:22 han.c
* -rwxrwxr-x 1 dj dj 16960  2월 24 00:21 newcp
*/
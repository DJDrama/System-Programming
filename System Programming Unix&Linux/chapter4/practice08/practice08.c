#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int rfd, wfd, n;
	
	char buf[BUFSIZ];
	
	rfd = open(argv[2], O_RDONLY);
	if(rfd == -1){
		perror("Open argv[2]");
		exit(1);
	}
	mode_t process_mask;
	process_mask = umask(0);
	mkdir(argv[1], 0777);
	umask(process_mask);
	wfd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(wfd==-1){
		perror("Open test/test.txt");
		exit(1);
	}
	
	while((n=read(rfd, buf, BUFSIZ)) > 0){
		if(write(wfd, buf, n)!=n) 
			perror("Write");
	}
	if(n==-1)
		perror("Read");
	
	int ret;
	ret = remove(argv[2]);
	if(ret == -1){
		perror("remove argv[2]");
		exit(1);
	}
	close(rfd);
	close(wfd);
	
	
}
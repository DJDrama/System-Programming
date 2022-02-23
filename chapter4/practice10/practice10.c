#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int fd, n;
	char buf[1];
	fd = open("atoz.txt", O_RDONLY);
	if(fd==-1){
		perror("Open");
		exit(1);
	}
	
	while((n=read(fd, buf, 1)) > 0){
		printf("%c", buf[0]);
		lseek(fd, 1, SEEK_CUR);
	}
	if(n==-1){
		perror("Read");
		exit(1);
	}
	close(fd);
}
/* 
* ,/a.out --> acegikmoqsuwy
*/
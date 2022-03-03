#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]){
	int fd, line_number, i;
	off_t file_len;
	ssize_t ret;
	char *buf;
	
	line_number=1;
	fd = open(argv[1], O_RDONLY);
	if(fd==-1){
		perror("open");
		return 1;
	}
	file_len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	buf = (char *) malloc(sizeof(char)* (int) file_len);
	
	int count=0;
	while(ret = read(fd, buf, 255) != 0) {
		if(ret == -1){
			if(errno == EINTR)
				continue;
			perror("read");
			break;
		}
	}

	i=0;
	printf("%d: ", line_number);
	while(buf[i]!='\0'){
		if(buf[i-1] == '\n'){
			printf("%d: ", ++line_number);
		}
		printf("%c", buf[i++]);
	}

	free(buf);
	close(fd);
	
}
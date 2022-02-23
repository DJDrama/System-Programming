#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int fd;
	int n;
	int line_number;
	int i;
	
	char buf[BUFSIZ];
	
	fd = open(argv[1], O_RDONLY);
	line_number=1;
	
	if((n=read(fd, buf, BUFSIZ)) == -1){
		perror("Read");
		exit(1);
	}
	
	buf[n]='\0';
	printf("%d:", line_number);
	
	i=0;
	while(buf[i]!='\0'){
		if(buf[i-1]=='\n')
			printf("%d:", ++line_number);
		printf("%c", buf[i++]);
	}
	close(fd);
}

/* gcc -o newcat han.c
* ./newcat han.c
*/
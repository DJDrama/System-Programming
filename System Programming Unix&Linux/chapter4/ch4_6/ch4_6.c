#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int fd, n;
	off_t start, cur;
	char buf[256];
	
	fd = open("linux.txt", O_RDONLY);
	if(fd==-1){
		perror("Open");
		exit(1);
	}
	
	start = lseek(fd, 0, SEEK_CUR);
	n = read(fd, buf, 255);
	buf[n]='\0';
	
	printf("Offset started=%d, n=%d, Read str=%s", (int) start, n, buf); // Linux System Programming (0~24) \0 (25)
	
	cur = lseek(fd, 0, SEEK_CUR); // File offset : add 0 to current offset
	printf("Offset cur=%d\n", (int) cur); // 25
	
	start = lseek(fd, 6, SEEK_SET); // File offset : 6 from start point --> 6
	n = read(fd, buf, 255);
	buf[n]='\0';
	printf("Offset start=%d, n=%d, Read str=%s", (int) start, n, buf); // System Programming (6~18) \0(19)
	
	close(fd);
}

/* ./a.out --> Open: No such file or directory
* vi linux.txt --> Linux System Programming
* ./a.out --> 
* Offset started=0, n=25, Read str=Linux System Programming
* Offset cur=25,
* Offset start=6, n=19, Read str=System Programming
*/
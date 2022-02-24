#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TIMEOUT 10
#define BUF_LEN 1024
#define MAX_LENGTH 80

int main(){
	int fd, n, ret;
	struct timeval tv;
	fd_set readfds, writefds;
	char w_arr[MAX_LENGTH], r_arr[MAX_LENGTH];
	
	tv.tv_sec = TIMEOUT;
	tv.tv_usec=0;
	
	char *fifo = "/tmp/dj";
	mkfifo(fifo, 0666);

	while(1){
		FD_ZERO(&readfds);
		FD_SET(STDIN_FILENO, &readfds);
		
		ret = select(STDIN_FILENO+1, &readfds, NULL, NULL, &tv);
		if(ret==-1){
			perror("select");
			exit(1);
		}else if(!ret){
			printf("%d seconds elapsed.\n", TIMEOUT);
			exit(1);
		}
		
		if(FD_ISSET(STDIN_FILENO, &readfds)){
			if((fd = open(fifo, O_RDONLY) ) == -1){
				perror("Read");
				exit(1);
			}
			read(fd, r_arr, sizeof(r_arr));
		
			printf("test_1: %s\n", r_arr);
			close(fd);
		}


		FD_ZERO(&writefds);
		FD_SET(STDOUT_FILENO, &writefds);
		ret = select(STDOUT_FILENO+1, NULL, &writefds, NULL, &tv);
		if(ret==-1){
			perror("select");
			exit(1);
		}else if(!ret){
			printf("%d seconds elapsed.\n", TIMEOUT);
			exit(1);
		}
		
		if(FD_ISSET(STDOUT_FILENO, &writefds)){
			if((fd = open(fifo, O_WRONLY)) == -1){
				perror("open");
				exit(1);
			}
			
			fgets(w_arr, MAX_LENGTH, stdin);
			write(fd, w_arr, sizeof(w_arr));
			close(fd);
		}
	}
	return 0;
	
}
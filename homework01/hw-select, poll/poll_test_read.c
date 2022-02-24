#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>

#define TIMEOUT 5
#define MSG_BUF 256

int main(){
	struct pollfd fds[1];
	int ret, rfd;
	
	char r_arr[MSG_BUF];
	
	char *fifo = "/tmp/dj";

	mkfifo(fifo, 0666);

	while(1){
		fds[0].fd  = STDOUT_FILENO;
		fds[0].events = POLLOUT; // read
		
		ret = poll(fds, 1, TIMEOUT*1000);
		if(ret == -1){
			perror("Poll");
			exit(1);
		}else if(!ret){
			printf("%d seconds elapsed.\n", TIMEOUT);
			exit(1);
		}
		
		if(fds[0].revents & POLLOUT){
			//printf("Log: stdin is readable\n");
			rfd = open(fifo, O_RDONLY);
			if(rfd==-1){
				perror("Read");
				exit(1);
			}
			read(rfd, r_arr, sizeof(r_arr));
			printf("from write: %s\n", r_arr);
			close(rfd);
		}
	}
	
}
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
	int ret, wfd;
	
	char buf[MSG_BUF];
	char w_arr[MSG_BUF];
	
	char *fifo = "/tmp/dj";

	mkfifo(fifo, 0666);

	while(1){
		fds[0].fd  = STDIN_FILENO;
		fds[0].events = POLLIN; // write
		
		ret = poll(fds, 1, TIMEOUT*1000);
		if(ret == -1){
			perror("Poll");
			exit(1);
		}else if(!ret){
			printf("%d seconds elapsed.\n", TIMEOUT);
			exit(1);
		}
		
		if(fds[0].revents & POLLIN){
			printf("Log: stdout is writable\n");
			wfd = open(fifo, O_WRONLY);
			if(wfd==-1){
				perror("Read");
				exit(1);
			}
			fgets(w_arr, MSG_BUF, stdin);
			write(wfd, w_arr, sizeof(w_arr));
			close(wfd);
		}
	}
	
}
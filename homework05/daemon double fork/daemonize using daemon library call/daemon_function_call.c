#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <errno.h>

int main(){
	printf("Daemonize!\n");
	int fd;
	
	if(daemon(0, 0) == -1){
		perror("daemon");
		return -1;
	}
	
	fd = open("/dev/tty47", O_RDWR);
	if(fd==-1){
		syslog(LOG_ERR, "failed to open\n");
		return 1;
	}
	
	sleep(120);
	return 0;
}
#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Daemonize!\n");
	
	if(daemon(0, 0) == -1){
		perror("daemon");
		return -1;
	}
	
	sleep(120);
	return 0;
}
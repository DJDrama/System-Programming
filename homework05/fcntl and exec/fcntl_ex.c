#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h> // for perror

int main(){
	int fd;

	fd = open("travel_wallet.txt", O_RDWR | O_CLOEXEC);
	
	if(fd==-1){
		perror("open");
		return -1;
	}
	
	if(execl("exec_file", "./exec_file", NULL) == -1){
		perror("execl");
		return -1;
	}
	
	printf("End of fcntl_ex\n");
	
	return 0;
}



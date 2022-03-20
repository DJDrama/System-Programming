#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h> // for EXIT_FAILURE
#include <stdio.h> // for perror

int main(){
	pid_t pid;
	pid = fork();

	if(pid==-1)
		perror("fork");

	/* Child Process */
	if(!pid){
		const char *args[] = {"windlass", NULL};
		int ret;

		ret = execv("/bin/windlass", args);
		if(ret==-1){
			perror("execv");
			exit(EXIT_FAILURE);
		}
	}
}
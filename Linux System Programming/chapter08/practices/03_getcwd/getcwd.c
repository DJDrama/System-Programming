#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_LEN 1024

int main(){
	char cwd[BUF_LEN];

	if(!getcwd(cwd, BUF_LEN)){
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	printf("cwd=%s\n", cwd);
	return 0;
}

/* results
# ./getcwd              
> cwd=/{absolute path}/System-Programming/Linux System Programming/chapter08/practices/03_getcwd
*/
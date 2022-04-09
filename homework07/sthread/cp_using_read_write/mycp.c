#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>


void * copy(void * arg){
	int n;
	int rfd, wfd;
	char buf[BUFSIZ];
	char **argv = (char**) arg;
	
  	/* open file for read */
  	rfd = open(argv[1], O_RDONLY);
  	if(rfd == -1){
  		perror("open");
  		exit(1);
  	}

	/* open file for write */
	wfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(wfd==-1){
		perror("open");
		exit(1);
	}
	
	while((n=read(rfd, buf, BUFSIZ)) > 0){
		if(write(wfd, buf, n)!=n)
			perror("Write");
	}
	
	/* close fds */
	close(rfd);
	close(wfd);
	
	return 0;
}

int main(int argc, char *argv[]){
	clock_t t;
	pthread_t thread;
	
	t = clock();

	/* create pthread */
	pthread_create(&thread, NULL, copy, &(*argv));
	
	/* join */
	pthread_join(thread, NULL);
	
	/* time  measurement */
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("Took %f seconds to execute\n", time_taken);
	return 0;
}
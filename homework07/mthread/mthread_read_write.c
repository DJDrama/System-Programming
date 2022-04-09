#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	char *source;
	char *dest;
	unsigned long offset;
	unsigned long size;
} FILE_OPTIONS;

void * copy(void *arg){
	FILE_OPTIONS *file_options;
	unsigned long size;
	int rfd, wfd, n;
	
	file_options = (FILE_OPTIONS *) arg;
	size = file_options->size;
	char buf[size];
	
	 /* open file for read */
  	rfd = open(file_options->source, O_RDONLY);
  	if(rfd == -1){
  		perror("open");
  		exit(1);
  	}
	
	/* open file for write */
	wfd = open(file_options->dest, O_WRONLY | O_CREAT, 0644);
	if(wfd==-1){
		perror("open");
		exit(1);
	}
	
	/* read & write */
	while((n=read(rfd, buf, size)) > 0){
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
	struct stat statbuf;
	int no_threads;
	int i;
	unsigned long divided_size;
	
	/* init Clock */
	t = clock();
	
	/* Ask For Threads */
	printf("How many threads do you want? ");
	scanf("%d", &no_threads);
	
	/* get file size */
  	if(stat(argv[1], &statbuf)==-1){
  		perror("stat");
  		return -1;
  	}

	/* FILE_OPTIONS init */
	divided_size = statbuf.st_size / no_threads;
	FILE_OPTIONS file_options[no_threads];
	file_options[0].source = argv[1];
	file_options[0].dest = argv[2];
	file_options[0].offset = 0;
	file_options[0].size = divided_size;
	
	for(i=1; i<no_threads; i++){
		file_options[i].source = argv[1];
		file_options[i].dest = argv[2];
		file_options[i].offset += file_options[i-1].size;
		file_options[i].size = divided_size;
	}
	
	/* thread init & create */
	pthread_t threads[no_threads];
	for(i=0; i<no_threads; i++){
		pthread_create(&threads[i], NULL, copy, &file_options[i]);
	}
	
	/* thread join */
	for(i=0; i<no_threads; i++){
			pthread_join(threads[i], NULL);
	}
	
	/* time  measurement */
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("Took %f seconds to execute\n", time_taken);
	return 0;
}
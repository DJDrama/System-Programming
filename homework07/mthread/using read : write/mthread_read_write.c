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
	int rfd, wfd, n, red;
	
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
	
	/* set file pointer */
	lseek(rfd, file_options->offset, SEEK_SET);
	lseek(wfd, file_options->offset, SEEK_SET);
	
	/* write */
	n=0;
	while(n < size){
		red = read(rfd, buf, size);
		write(wfd, buf, red);
		n += red;
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
	pthread_t *threads;
	
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
	printf("Number of Threads: %d\n", no_threads);
	threads = malloc(sizeof(pthread_t) * no_threads);

	for(i=0; i<no_threads; i++){
		int err = pthread_create(&threads[i], NULL, copy, (void*) &file_options[i]);
		if(err){
			printf("%d thread error: %d\n", i, err);
			return -1;
		}
	}
	

	/* thread join */
	for(i=0; i<no_threads; i++){
			pthread_join(threads[i], NULL);
	}
	
	free(threads);

	/* time  measurement */
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("Took %f seconds to execute\n", time_taken);
	return 0;
}
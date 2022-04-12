#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	int id; // thread id
	char *source;
	char *dest;
	unsigned long offset;
	unsigned long size;
} FILE_OPTIONS;

void * copy(void *arg){
	struct timeval t0, t1, dt;
	FILE_OPTIONS *file_options;
	unsigned long size;
	int rfd, wfd, n, red;
	
	gettimeofday(&t0, NULL);
	
	file_options = (FILE_OPTIONS *) arg;
	size = file_options->size;
	
	char *buf;
	buf = (char *) malloc(sizeof(char)*size);
	
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
	
	free(buf);
	
	/* close fds */
	close(rfd);
	close(wfd);
	
	gettimeofday(&t1, NULL);
	timersub(&t1, &t0, &dt);
	
	printf("Time Measure: (thread: %d) took %ld.%06ld sec\n", file_options->id, dt.tv_sec, dt.tv_usec);
	
	return 0;
}

int main(int argc, char *argv[]){
	struct stat statbuf;
	int no_threads;
	int i;
	unsigned long divided_size, offset;
	pthread_t *threads;

	
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
	file_options[0].id = 0;
	file_options[0].source = argv[1];
	file_options[0].dest = argv[2];
	file_options[0].offset = 0;
	file_options[0].size = divided_size;
	
	for(i=1; i<no_threads; i++){
		file_options[i].id = i;
		file_options[i].source = argv[1];
		file_options[i].dest = argv[2];
		offset += file_options[i-1].size;
		file_options[i].offset = offset;
		file_options[i].size = divided_size;
	}
	

	
	/* thread init & create */
	printf("Number of Threads: %d\n", no_threads);
	threads = malloc(sizeof(pthread_t) * no_threads);
	if(threads == NULL){
		perror("malloc");
		return -1;
	}

	int err;
	for(i=0; i<no_threads; i++){
		if((err=pthread_create(&threads[i], NULL, copy, (void*) &file_options[i]))!=0){
			perror("pthread_create");
			return -1;
		}
	}
	

	/* thread join */
	err=0;
	for(i=0; i<no_threads; i++){
		if((err = pthread_join(threads[i], NULL)) !=0 ){
			perror("pthread_join");
			return -1;
		}
	}
	
	
	free(threads);

	return 0;
}
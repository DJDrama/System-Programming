#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	clock_t t;
	char **buf;
	int iov_count, i;
	struct iovec *iov;
	ssize_t nr;
	int rfd, wfd;
	int read_size = 8192;

	t = clock();

	/* open file for read only */
	rfd = open(argv[1], O_RDONLY);
	if(rfd == -1){
		perror("open");
		return 1;
	}

	/* get file size */
	int file_size = lseek(rfd, 0, SEEK_END);
	iov_count = file_size / read_size;
	if(file_size % read_size !=0)
		iov_count++;
	lseek(rfd, 0, SEEK_SET);

	/* malloc iov and buf */
	iov = malloc(iov_count * sizeof(struct iovec));
	buf = malloc(sizeof(char *) * iov_count);
	for(i=0; i<iov_count; i++){
		buf[i] = malloc(sizeof(char)*read_size);
	}

	/* set iovec */
	for(i=0; i<iov_count; i++){
		iov[i].iov_base = buf[i];
		iov[i].iov_len = read_size;
	}

	/* readv */
	nr = readv(rfd, iov, iov_count);
	if(nr == -1){
		perror("readv");
		return 1;
	}

	/* open file for write */
	wfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(wfd==-1){
		perror("open");
		return 1;
	}

	/* writev */
	nr = writev(wfd, iov, iov_count);
	if(nr==-1){
		perror("writev");
		return 1;
	}


	close(rfd);
	close(wfd);

	/* free memory */
	for(i=0; i<iov_count; i++)
		free(buf[i]);
	free(buf);
	free(iov);

	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("Took %f seconds to execute\n", time_taken);
	return 0;
}
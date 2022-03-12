#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	clock_t t;

	caddr_t source_addr, dest_addr;
	char* source, dest;
	struct stat statbuf;
	int rfd, wfd;

	/* in order to get file size */
  	if(stat(argv[1], &statbuf)==-1){
  		perror("stat");
  		return -1;
  	}

  	/* open file for read */
  	rfd = open(argv[1], O_RDWR);
  	if(rfd == -1){
  		perror("open");
  		return -1;
  	}

  	/* mmap PROT_READ */
  	source_addr = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, rfd, 0);
  	if(source_addr == MAP_FAILED){
  		perror("source_addr mmap");
  		return -1;
  	}


  	/* open file for write(O_RDWR is the key) */
  	wfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
  	if(ftruncate(wfd, (off_t) statbuf.st_size) == -1){
  		perror("ftruncate");
  		return -1;
  	}

  	/* mmap PROT_READ or PROT_WRITE */
  	dest_addr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, wfd, 0);
  	if(dest_addr == MAP_FAILED){
  		perror("dest_addr mmap");
  		return -1;
  	}

  	/* mem copy */
  	memcpy(dest_addr, source_addr, statbuf.st_size);

  	/* remove memory mapping */
  	munmap(source_addr, statbuf.st_size);
	munmap(dest_addr, statbuf.st_size);

	/* close files */
  	close(rfd);
  	close(wfd);


	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("Took %f seconds to execute\n", time_taken);
	return 0;
}
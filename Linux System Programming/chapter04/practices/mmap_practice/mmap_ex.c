#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char* argv[]){
	struct stat sb;
	off_t len;
	char *p;
	int fd;

	if(argc < 2){
		fprintf(stderr, "Usage: $s <file>\n", argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("open");
		return 1;
	}

	if(fstat(fd, &sb) == -1){
		perror("fstat");
		return 1;
	}

	if (!S_ISREG(sb.st_mode)){ // S_ISREG: 주어진 파일이 디바이스 파일이나 디렉터리가 아닌 일반 파일인지 점검.
		fprintf(stderr, "%s is not a file\n", argv[1]);
		return 1;
	}

	p = mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

	if(p == MAP_FAILED){
		perror("mmap");
		return 1;
	}

	if(close(fd) == -1){
		perror("close");
		return 1;
	}

	for(len=0; len<sb.st_size; len++)
		putchar(p[len]);

	if(munmap(p, sb.st_size)==-1){
		perror("munmap");
		return 1;
	}
	return 0;
}
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	struct stat sb;
	int ret;

	if(argc<2){
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return 1;
	}

	ret = stat(argv[1], &sb);
	if(ret){
		perror("stat");
		return 1;
	}

	printf("%s is %lld bytes\n", argv[1], sb.st_size);
	return 0;
}

/* results 

# ./stat stat.c
 > stat.c is 361 bytes

 */
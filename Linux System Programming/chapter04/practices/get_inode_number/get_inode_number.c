#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
*	get_inode - 주어진 fd에 연결된 파일의 inode 반환. 실패 시 -1 반환.
*/

int get_inode(int fd){
	struct stat buf;
	int ret;
	ret = fstat(fd, &buf);
	if(ret<0){
		perror("fstat");
		return -1;
	}
	return buf.st_ino;
}

int main(int argc, char* argv[]){
	int fd, inode;

	if(argc < 2){
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if(fd<0){
		perror("open");
		return 1;
	}

	inode = get_inode(fd);
	printf("%d\n", inode); // 예: 60868171 출력. (주어진 파일의 inode 번호 출력)
	return 0;
}
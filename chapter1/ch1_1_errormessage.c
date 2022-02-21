#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

int main(){
	FILE *fp;
	
	if((fp=fopen("test.txt", "r")) == NULL){
		printf("errno=%d\n", errno);
		perror("test.txt");
		exit(1);
	}
	fclose(fp);
	
}


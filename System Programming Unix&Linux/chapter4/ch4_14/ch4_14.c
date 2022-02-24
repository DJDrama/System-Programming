#include <stdlib.h>
#include <stdio.h>

int main(){
	FILE *rfp, *wfp;
	char buf[BUFSIZ]; //8192
	int n;
	
	if((rfp = fopen("linux.txt", "r")) == NULL){
		perror("fopen: linux.txt");
		exit(1);
	}
	
	if((wfp = fopen("linux.out", "a")) == NULL){
		perror("fopen: linux.out");
		exit(1);
	}
	
	
	while((n=fread(buf, sizeof(char)*2, 4, rfp)) > 0) {
		fwrite(buf, sizeof(char)*2, n, wfp); // does not need to put extra '\0'', while read needs '\0' at the last position
	}
	
	fclose(rfp);
	fclose(wfp);
}

/* vi linux.txt --> Linux System Programming\nHanbit Academy
* ./a.out
* ls linux.out --> Linux System Programming\nHanbit Academy
* ./a.out
* ls linux.out --> Linux System Programming\nHanbit Academy\nLinux System Programming\nHanbit Academy
*/
	
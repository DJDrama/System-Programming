#include <stdlib.h>
#include <stdio.h>

int main(){
	FILE *rfp, *wfp;
	int c;
	
	if((rfp=fopen("linux.txt", "r")) == NULL){
		perror("fopen: linux.txt");
		exit(1);
	}
	
	if((wfp=fopen("linux.out", "w")) == NULL){
		perror("fopen: linux.out");
		exit(1);
	}
	
	while((c=fgetc(rfp)) != EOF){
		fputc(c, wfp);
	}
	
	fclose(rfp);
	fclose(wfp);
}

/* ./a.out --> fopen: linux.txt: No such file or directory
* vi linux.txt --> Linux System programming
* ./a.out
* ls --> a.out ch4_11.c linux.out linux.txt
* cat linux.out --> Linux System Programming
*/
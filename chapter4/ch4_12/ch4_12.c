#include <stdlib.h>
#include <stdio.h>

int main(){
	FILE *rfp, *wfp;
	char buf[BUFSIZ];
	
	printf("BUFSIZE: %d\n", BUFSIZ); // BUFSIZ = 8192
	
	if((rfp = fopen("linux.txt", "r")) == NULL){
		perror("fopen: linux.txt");
		exit(1);
	}
	
	if((wfp = fopen("linux.out", "a")) == NULL){ // append
		perror("fopen: linux.out");
		exit(1);
	}
	
	while(fgets(buf, BUFSIZ, rfp) != NULL){
		fputs(buf, wfp);
	}
	
	fclose(rfp);
	fclose(wfp);
}

/* ./a.out 
* appends string from linux.txt to linux.out
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *rfp, *wfp;
	char buf[BUFSIZ];
	
	rfp = fopen(argv[1], "r");
	if(!rfp){
		perror("fopen");
		return 1;
	}
	
	wfp = fopen(argv[2], "w");
	if(!wfp){
		perror("fopen");
		return 1;
	}
	
	while(fgets(buf, BUFSIZ, rfp)!=NULL) {
		fputs(buf, wfp);
	}
	
	fclose(rfp);
	fclose(wfp);
	
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	clock_t t;
	t = clock();
	
	FILE *rfp, *wfp;
	int c;
	
	if((rfp = fopen(argv[1], "r")) == NULL){
		perror("fopen: argv[1]");
		return 1;
	}
	
	if((wfp = fopen(argv[2], "w")) == NULL){
		perror("fopen: argv[2]");
		return 1;
	}
	
	while((c = fgetc(rfp))!=EOF){
		fputc(c, wfp);
	}
	
	fclose(rfp);
	fclose(wfp);
	
	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("took %f seconds to execute\n", time_taken);
	return 0;
	
}
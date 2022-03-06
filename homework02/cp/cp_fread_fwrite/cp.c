#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
		clock_t t;
	t = clock();
	FILE *rfp, *wfp;
	char buf[BUFSIZ];
	int n;
	
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
	
	while((n = fread(buf, 1, BUFSIZ, rfp)) > 0){
		fwrite(buf, 1, n, wfp);
	}
	
	fclose(rfp);
	fclose(wfp);

	t = clock() - t;
	double time_taken = ((double) t) / CLOCKS_PER_SEC;
	printf("took %f seconds to execute\n", time_taken);
	return 0;
}
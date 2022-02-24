#include <stdlib.h>
#include <stdio.h>

int main(){
	FILE *rfp;
	char buf[BUFSIZ]; // 8192
	int n;
	
	if((rfp = fopen("linux.txt", "r")) == NULL){
		perror("fopen: linux.txt");
		exit(1);
	}
	
	while ((n=fread(buf, sizeof(char)*2, 4, rfp)) >0){ // sizeof(char) = 1, sizeof(char)*2 = 2, total 8 bytes
		buf[8] = '\0';
		printf("n=%d, buf=%s\n", n, buf);
	}
	fclose(rfp);
}

/* ./a.out --> fopen: linux.txt: No such file or directory
* vi linux.txt --> Linux System Programming\nHanbig Academy
* ./a.out
* n=4, buf=Linux Sy
* n=4, buf=stem Pro
* n=4, buf=gramming
* n=4, buf=
* Hanbit <-- \n at front and space is there(7)
* n=4, buf=Academy (last bytes)
*
*/

#include <stdlib.h>
#include <stdio.h>

int main(){
	char *val;
	
	val = getenv("TERM");
	if (val == NULL)
		printf("TERM not defined\n");
	else
		printf("1. TERM=%s\n", val);
	
	setenv("TERM", "vt100", 0);
	val = getenv("TERM");
	printf("2. TERM = %s\n", val);
	
	setenv("TERM", "vt100", 1);  // use 1(non zero) value in order to overwrite
	val = getenv("TERM");
	printf("3. TERM=%s\n", val);
	
	return 0;
}

/*
1. TERM=xterm-256color
2. TERM = xterm-256color
3. TERM=vt100
*/
#include <stdio.h>
#include <unistd.h>

int main(){
	long atexit_max;

	atexit_max = sysconf(_SC_ATEXIT_MAX);
	printf("atexit_max=%ld\n", atexit_max);
}

/*
atexit_max=2147483647(2^31-1)
*/
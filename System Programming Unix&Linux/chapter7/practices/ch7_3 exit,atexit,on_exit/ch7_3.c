#include <stdlib.h>
#include <stdio.h>

void cleanup1() {
	printf("Clieanup 1 is called\n");
}

void cleanup2(int status, void *arg){
	printf("Cleanup 2 is called: %ld.\n", (long) arg);
}

int main(){
	atexit(cleanup1);
	on_exit(cleanup2, (void *) 20);

	exit(0);
}

/* (함수가 예약 순서와 반대로 호출되었음)
Cleanup 2 is called: 20.
Clieanup 1 is called
*/
#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Long running process Started!\n");
	sleep(120);
	printf("Long running process Terminated!\n");
	return 0;
}
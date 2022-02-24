#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b);

int main(int argc, char *argv[]){
	int small, big;
	small = atoi(argv[1]);
	big = atoi(argv[2]);
	printf("sum from %d to %d: %d\n", small, big, sum(small, big));
}

int sum(int a, int b){
	int i;
	int sum;
	sum=0;
	for(i=a; i<=b; i++)
		sum+=i;
	return sum;
}
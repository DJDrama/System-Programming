#include <stdlib.h>
#include <stdio.h>

int main(){
	int* ptr;
	ptr = (int*)malloc(sizeof(int)*200);
	
	free(ptr);
	
}
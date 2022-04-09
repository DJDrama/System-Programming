#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * start_thread(void *message){
	printf("%s\n", (const char *) message);
	return message;
}

int main(){
	pthread_t thing1, thing2;
	const char *message1 = "Thing 1";
	const char *message2 = "Thing 2";
	
	pthread_create(&thing1, NULL, start_thread, (void *) message1);
	pthread_create(&thing2, NULL, start_thread, (void *) message2);
	
	
	pthread_join(thing2, NULL);
	pthread_join(thing1, NULL);
	
	return 0;
}

// gcc -Wall -Werror -pthread 7.7.8.c -o threading_example

/*
$ ./threading_example 
Thing 1
Thing 2

*/
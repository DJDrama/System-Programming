#include <sys/types.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int i;
	time_t t;
	struct tms buf;
	clock_t ct, t1, t2;
	ct = sysconf(_SC_CLK_TCK);  // search clock tick value (1sec = 100 ticks)
	printf("Clock tick: %ld\n", ct);
	
	if((t1=times(&buf))==-1){
		perror("times 1");
		exit(1);
	}
	
	for(i=0; i<999999999; i++)
		time(&t);
	sleep(1);
	
	if((t2=times(&buf))==-1){
		perror("times 2");
		exit(1);
	}
	
	printf("t1: %ld\n", t1);
	printf("t2: %ld\n", t2);
	printf("utime: %ld\n", buf.tms_utime); // user time
	printf("stime: %ld\n", buf.tms_stime); // system time
	printf("Real time: %.1f sec\n", (double)(t2-t1) / ct);
	printf("User time: %.1f sec\n", (double)buf.tms_utime / ct); // sleep 1 adds 1 second
	printf("System time: %.1f sec\n", (double)buf.tms_stime/ct);
	return 0;
}

/*
Clock tick: 100
t1: 1721083258
t2: 1721083553
utime: 189
stime: 0
Real time: 3.0 sec
User time: 1.9 sec
System time: 0.0 sec

*/
#include <sys/sysinfo.h>
#include <stdio.h>

int main(){
	struct sysinfo info;
	sysinfo(&info);
	
	printf("Total ram: %ld\n", info.totalram);
	printf("Free ram: %ld\n", info.freeram);
	printf("Num of Processes: %d\n", info.procs);
	
	return 0;
}
	
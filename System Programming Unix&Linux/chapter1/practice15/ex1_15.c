#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	int n;
	extern char *optarg;
	extern int optind;
	if(argc <= 1)
		printf("Options: -p, -n, -h\n");
	while((n = getopt(argc, argv, "pn:h")) != -1){
		switch(n){
			case 'p':
				printf("Welcome Linux System Programming!\n");
				break;
			case 'n':
				printf("Nice to meet %s\n", optarg);
				break;
			case 'h':
				printf("Options: -p, -n, -h\n");
				break;
		}
	}
}
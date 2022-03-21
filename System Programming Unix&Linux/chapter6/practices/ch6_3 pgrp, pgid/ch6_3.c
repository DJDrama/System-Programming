#include <unistd.h>
#include <stdio.h>


int main(){
	printf("PID: %d\n", (int) getpid());
	printf("PGRP: %d\n", (int) getpgrp());
	printf("PGID(0): %d\n", (int) getpgid(0));
	printf("PGID(18020): %d\n", (int) getpgid(18020));
}

/*
(MAC)
# ps
  PID TTY           TIME CMD
47770 ttys000    0:00.13 -zsh

# ./a.out
PID: 48916
PGRP: 48916
PGID(0): 48916 // 단독 프로세스여서 프로세스 그룹에 홀로 속해 있기 때문에 pid와 pgid가 같음
PGID(18020): -1

*/

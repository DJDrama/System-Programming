#include <unistd.h>
#include <stdio.h>

int main(){
	printf("PID: %d\n", (int) getpid());
	printf("PPID: %d\n", (int) getppid());
}

/*
[MAC]
PID: 48257
PPID: 47770

# ps (터미널에서 실행 중인 프로세스 보기)
  PID TTY           TIME CMD
47770 ttys000    0:00.10 -zsh

ttys란?
(TeleTYpewriter, TTY) Teletypewriter originally and now also means any terminal on Linux/Unix systems.
*/
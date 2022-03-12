#include <sys/mman.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void handler(int dummy){
	;
}

int main(){
	key_t key;
	int shmid;
	void *shmaddr;

	char buf[1024];
	sigset_t mask;

	key = ftok("shmfile", 1);
	shmid = shmget(key, 1024, IPC_CREAT | 0666); // 공유 메모리 식별자 생성.

	sigfillset(&mask);
	sigdelset(&mask, SIGUSR1);
	signal(SIGUSR1, handler); // 시그널을 받아서 handler 함수 실행.


	printf("Server waiting...\n\n");
	sigsuspend(&mask);


	printf("Server start...\n");
	shmaddr = shmat(shmid, NULL, 0); // shmaddr인자: NULL 이면 시스템이 알아서 적절한 주소에 공유 메모리 연결, shmflg인자: 0이면 공유 메모리에 대해 일기 / 쓰기 가능.
	strcpy(buf, shmaddr);
	printf("Server received: %s\n", buf);

	strcpy(shmaddr, "Travel Wallet!\n");
	sleep(3);
	shmdt(shmaddr); // 공유 메모리 연결 해제.

}
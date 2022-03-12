#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	key_t key;
	int shmid;
	void *shmaddr;
	char buf[1024];

	key = ftok("shmfile", 1);
	shmid = shmget(key, 1024, 0); // 마지막 인자:  0 -> 이미 생성된 shared memory identifier 있을 때, 읽기/쓰기 권한이 있을 때, 연관된 shared memory identifier을 리턴.

	shmaddr = shmat(shmid, NULL, 0);
	strcpy(shmaddr, "Please send me a message!\n");

	kill(atoi(argv[1]), SIGUSR1); // 명령행 인자로 받은 listener의 PID를 지정하고 SIGUSR1 시그널을 보낸다.
	sleep(2); // 잠시 기다렸다가 공유 메모리에서 Server 보낸 응답을 읽어 출력.
	strcpy(buf, shmaddr);

	printf("Response from Server: %s\n", buf);
	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID, NULL); // IPC_RMID: shmid로 지정한 공유 메모리를 제거하고 관련된 데이터 구조체 제거.
}
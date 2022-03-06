#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int shmid, i;
	char *shmaddr, *shmaddr2;

	shmid = shmget(IPC_PRIVATE, 20, IPC_CREAT|0644); // 키를 IPC_PRIVATE 지정, 공유 메모리 20바이트 크기로 생성.
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}

	switch(fork()){ // 자식 프로세스 생성
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			shmaddr = (char *) shmat(shmid, (char *) NULL, 0); // 공유 메모리 연결
			printf("Child Process ====\n");
			for(i=0; i<10; i++) 
				shmaddr[i] = 'a'+i; // 문자 10개 기록.
			shmdt((char *)shmaddr); // 공유 메모리 해제
			exit(0);
			break;
		default :
			wait(0); // 일단 자식 프로세스가 종료하기를 기다린다.
			shmaddr2 = (char *)shmat(shmid, (char *) NULL, 0); // 공유 메모리 연결
			printf("Parent Process =====\n");
			for(i=0; i<10; i++)
				printf("%c ", shmaddr2[i]); // 내용 읽어서 출력.
			printf("\n");
			sleep(5); // 다른 터미널에서 ipcs 명령으로 공유 메모리의 상태를 확인하기 위해서이다. 공유 메모리가 생겼다가, 프로세스가 종료된 후에는 삭제된다.
			shmdt((char *)shmaddr2); // 공유 메모리 해제
			shmctl(shmid, IPC_RMID, (struct shmid_ds *) NULL); // 공유 메모리 제거, 관련된 데이터 구조체 제거.
			break;

	}
}
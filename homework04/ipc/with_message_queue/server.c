#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf {
	long type; // 메세지 유형(양수)
	char text[128]; // msgsnd() 함수의 msgsz로 지정한 크기의 버퍼로 메시지 내용이 저장됨.
};

int main(){
	key_t key;
	int msgid;
	struct mymsgbuf msg;
	char input[128];


	// returns a key base don path and id that is usable in subsequent calls to msget(), semget(), shmget()
	// returns the same key value for all paths that name the same file, when called with the same id value.
	key = ftok("keyfile", 1);


	msgid = msgget(key, IPC_CREAT | 0644); // 메시지 큐 식별자 리턴(음수가 아닌 정수), IPC_CREATE: 새로운 키면 식별자를 새로 생성,
	if(msgid==-1){ // 에러, 메시지 전송 하지 않음.
		perror("msgget");
		exit(1);
	}

	// (네번째 인자) msgtyp=1 -> msgtyp로 지정한 유형과 같은 메세지를 읽어온다(여기서는 1로 지정한).
	// (다섯번째 인자) msgflg=0 -> 메세지 큐에 메세지가 올 때까지 기다린다.
	// 수행 성공: 읽어온 메세지의 바이트 수를 리턴.
	msgrcv(msgid, &msg, sizeof(msg.text), 1, 0); 
	printf("From Client: %s\n", msg.text);

	printf("To Client: ");
	fgets(input, sizeof(input), stdin);

	msg.type=2;
	strcpy(msg.text, input);

	/* msgsend-> 식별자, 버퍼 주소, 크기, 0 = 블록 모드. */
	if(msgsnd(msgid, (void *) &msg, sizeof(msg.text), 0) == -1){
		perror("msgsnd");
		exit(1);
	}
}
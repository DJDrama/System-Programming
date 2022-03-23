#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	printf("--> Before exec function\n");

	if(execlp("ls", "ls", "-a", (char*)NULL) == -1){
		perror("execlp");
		exit(1);
	}

	printf("--> After exec function\n"); // 실행되지 않음: execlp 함수에서 프로세스 이미지가 ls 명령의 이미지로 바뀌었기 때문.
}
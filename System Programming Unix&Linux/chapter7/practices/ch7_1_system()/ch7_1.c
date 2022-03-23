#include <stdlib.h>
#include <stdio.h>

int main(){
	int ret;
	ret = system("ps -ef | grep sshd > sshd.txt");
	printf("Return Value: %d\n", ret);
}

/*
(Mac)
% ./a.out 
Return Value: 0

% cat sshd.txt 
  501 38251 38250   0  3:18PM ttys000    0:00.00 sh -c ps -ef | grep sshd > sshd.txt // -c: 문자열에서 명령을 읽어오라.
  501 38253 38251   0  3:18PM ttys000    0:00.00 grep sshd
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
	int status;
	pid_t pid;

	pid = fork();

	pid = waitpid(pid, &status, WNOHANG);
	if(pid == -1){
		perror("waitpid");
	}else {
		printf("pid=%d\n", pid);
		if(WIFEXITED(status))
			printf("Normal termination with exit status=%d\n", WEXITSTATUS(status));

		if(WIFSIGNALED(status))
			printf("Killed by signal=%d%s\n", WTERMSIG(status), WCOREDUMP(status) ? " (dumped core)" : "");

	}

	sleep(2);

}

/*
pid=0
Killed by signal=37 // 37	0x25	SIGRTMIN+3	Real-time signal 3 (kill -l)
waitpid: No child processes
*/
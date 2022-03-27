#include <fcntl.h>
#include <stdio.h>
#include <linux/fs.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <stdlib.h>

/*
1. fork() : exit parent -> new process not to be a process group leader
2. setsid(): become a process group and session group leader.
3. fork() : parent(session group leader) can exit.non-session group leader, can never regain a controlling terminal.
4. chdir("/") : ensure our process doesn't keep any directory in use.
5. umask(0) : we have complete control over the permissions of anything we write. (optional step)
6. close() : use _SC_OPEN_MAX to close max file descriptors.
7. Establish new open descriptors for stdin, stdout and sterr. (we may open logfile using stdout, stderr, open 'dev/null' as stdin, open 'dev/console' as stderr and/or stdout, and '/dev/null' as stdin, and etc.
*/
void double_fork_daemonize();

int main(void){
	double_fork_daemonize();
	
	while(1){
		syslog(LOG_NOTICE, "DF Daemon Started!\n");
		sleep(120);
		break;
	}
	
	syslog(LOG_NOTICE, "DF Daemon Terminated!\n");
	closelog();
	
	return 0;
}

void double_fork_daemonize(){
	pid_t pid;
	int i;
	
	/* Create new process */
	pid = fork();
	if(pid==-1)
		exit(EXIT_FAILURE);
	else if(pid!=0) // Parent Process
		exit(EXIT_SUCCESS);
	
	/* create new session and process group */
	if(setsid() == -1)
		exit(EXIT_FAILURE);
	
	/* fork again */
	pid = fork();
	if(pid==-1)
		exit(EXIT_FAILURE);
	else if(pid!=0)
		exit(EXIT_SUCCESS);
	
	/* set the working directory to the root directory */
	if(chdir("/") == -1)
		exit(EXIT_FAILURE);
	
	/* set new file permissions -> 0666 */
	umask(0);
	
	/* close all open file descriptors */
	for(i=sysconf(_SC_OPEN_MAX); i>=0; i--)
		close(i);
	
	/* redirect fd's 0, 1, 2, to /dev/null */
	open("/dev/null", O_RDWR); /* stdin */
	dup(0); /* stdout */
	dup(0); /* stderror */
}
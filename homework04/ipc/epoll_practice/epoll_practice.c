#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <string.h>

#define MAX_EVENTS 64

int main(){

	struct epoll_event event, *events;
	int nr_events, i, epfd;
	int is_running=1;

	/* epoll instance creation */
	epfd = epoll_create1(); //  새로운 epoll 인스턴스 생성하고 연관된 파일 디스크립터를 반환.
	if(epfd == -1){
		perror("epoll_create1");
		return 1;
	}

	/* epoll control */
	event.events = EPOLLIN; //  파일 읽기가 지연되지 않고 바로 가능한지 감시
	event.data.fd = 0;

	if(epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &event) < 0){
		perror("epoll_ctl");
		close(epfd);
		return 1;
	}

	/* malloc events */
	events = malloc(sizeof(struct epoll_event) * MAX_EVENTS);
	if(!events){
		perror("malloc");
		close(epfd);
		return 1;
	}

	while(is_running){
		printf("Running...\n");
		nr_events = epoll_wait(epfd, events, MAX_EVENTS, -1); // timeout이 -1인 경우: 이벤트가 발생할 때까지 해당 호출은 반환되지 않음.
		if(nr_events < 0){
			perror("epoll_wait");
			free(events);
			close(epfd);
			return 1;
		}

		for(i=0; i<nr_events; i++){
			printf("event=%ld on fd=%d\n", events[i].events, events[i].data.fd);
		}
	}

	close(epfd); // epoll_create1()에서 반환하는 fd는 폴링이 끝난 뒤 반드시 close() 시스템 콜로 닫아줘야 한다.
	free(events);
}
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
  int fd;
  pid_t pid;
  caddr_t addr;
  struct stat statbuf;

  if(argc!=2){
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(1);
  }

  if(stat(argv[1], &statbuf) == -1){
    perror("stat");
    exit(1);
  }

  if((fd=open(argv[1], O_RDWR)) == -1){
    perror("open");
    exit(1);
  }

  addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t) 0);
  if(addr == MAP_FAILED){
    perror("mmap");
    exit(1);
  }

  close(fd);

  switch(pid = fork()){ // 자식 프로세스 생성.
    case -1: // fork failed
      perror("fork");
      exit(1);
      break;
    case 0: // child process
      printf("1. Child Process: addr=%s", addr); // 자식 프로세스는 부모 프로세스를 상속하므로 매핑된 메모리의 시작주소인 addr 공유.
      sleep(1);
      addr[0] = 'x';
      printf("2. Child Process: addr=%s", addr);
      sleep(2);
      printf("3. Child Process: addr=%s", addr);
      break;
    default: // parent Process
      printf("1. Parent process: addr=%s", addr);
      sleep(2);
      printf("2. Parent process: addr=%s", addr);
      addr[1]='y';
      printf("3. Parent process: addr=%s", addr);
      break;
  }

  // 실제로는 wait 함수를 사용하거나 시그널을 사용해 읽고 쓰는 순서 조정 가능.

}

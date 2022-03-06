#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
  int fd;
  caddr_t addr;
  struct stat statbuf;

  if(argc!=2){
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(1);
  }
  if(stat(argv[1], &statbuf)==-1){
    perror("stat");
    exit(1);
  }

  if((fd = open(argv[1], O_RDWR)) == -1){
    perror("open");
    exit(1);
  }

  addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t) 0);
  if(addr == MAP_FAILED){
    perror("mmap");
    exit(1);
  }
  close(fd);
  printf("%s", addr); // 파일을 닫은 후에도 파일 내용이 모두 출력된다.

  if(munmap(addr, statbuf.st_size) == -1){
    perror("munmap");
    exit(1);
  }

  // zsh: segmentation fault  ./ch9_2 mmap.dat
  printf("%s", addr); // SIGSEGV 시그널 발생해 코어 덤프를 생성하고 프로세스 종료. 이미 메모리 매핑 해제되어 사용 권한이 없는 메모리에 접근했기 때문.
}

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
  int fd, pagesize, length;
  caddr_t addr;
  struct stat statbuf;

  pagesize = sysconf(_SC_PAGESIZE); // 시스템에 설정된 페이지 크기를 구한다. (mmap() 함수에서 페이지 단위로 메모리를 매핑하기 때문)
  length = 1 * pagesize;

  if((fd = open("m.dat", O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1){
    perror("open");
    exit(1);
  }

  if(ftruncate(fd, (off_t) length) == -1){ // 함수를 사용해 파일 크기를 페이지 크기로 증가.
    perror("ftruncate");
    exit(1);
  }

  addr = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t) 0);
  if(addr == MAP_FAILED){
    perror("mmap");
    exit(1);
  }

  close(fd);
  strcpy(addr, "ftruncate TEST\n");

}

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <libgen.h>

void copy_directory(char *src_path, char *dest_path);
void copy_recursively(char *src, char *dest);
void copy_file(char *src_path, char *dest_path, char* filename);

int main(int argc, char *argv[]){
	if(argc<4){
		fprintf(stderr, "usage: %s -r {source directory} {dest directory}\n", argv[0]);
		return 1;
	}

	char *src_path = argv[2];
	char *dest_path = argv[3];

	copy_directory(src_path, dest_path);
	return 0;
}

void copy_directory(char *src_path, char *dest_path){
	DIR *dest_dir;
	if((dest_dir = opendir(dest_path)) == NULL){
		if(mkdir(dest_path, 0755) == -1){
			perror("mkdir");
		}
	} else {
		closedir(dest_dir);
	}
	copy_recursively(src_path, dest_path);
}

void copy_recursively(char *src, char *dest){
	int errno;
	DIR *src_dir, *dest_dir;
	char *src_path, *dest_path;
	struct dirent *entry;


	printf("src: %s dest: %s\n", src, dest);

	if(strcmp(src, ".") == 0 || strcmp(src, "..") == 0){
		return ;
	}

	// no src directory
	if((src_dir = opendir(src)) == NULL){ 
		return ;
	}

	// create dest path
	dest_path = (char *) malloc(sizeof(char) * (strlen(dest) + 1 + strlen(basename(src))));
	strcpy(dest_path, dest);
	if(strcmp(src, basename(src))!=0){
		strcat(dest_path, "/");
		strcat(dest_path, basename(src));
	}
	printf("dest_path: %s\n", dest_path);
	// check directory
	if((dest_dir = opendir(dest_path)) == NULL){
		if(mkdir(dest_path, 0755) == -1){
			perror("mkdir");
		}
	}else{
		closedir(dest_dir);
	}

	errno=0;
	while((entry = readdir(src_dir))!=NULL){
		printf("entry->d_name: %s\n", entry->d_name);
		switch(entry -> d_type){
			case DT_DIR:
				printf("DT_DIR\n");
				if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name, "..")!=0){
					src_path = (char *) malloc (sizeof(char) * (strlen(src) + 1 + strlen(entry->d_name) ));
					strcpy(src_path, src);
					strcat(src_path, "/");
					strcat(src_path, entry->d_name);

					printf("Before copy_recursively %s %s\n", src_path, dest_path);
					copy_recursively(src_path, dest_path);
					
					if(src_path != NULL){
						printf("free src_path\n");
						free(src_path);
					}
				}
				break;
			case DT_REG:
				printf("DT_REG: %s\n", entry->d_name);
			case DT_UNKNOWN:
				printf("DT_UNKNOWN\n");
				copy_file(src, dest_path, entry->d_name);
				break;
			default: 
				break;
		}
	}

	if(errno && !entry){
		perror("readdir");
	}

	if(dest_path != NULL){
		printf("free dest_path\n");
		free(dest_path);
	}

	closedir(src_dir);
}

void copy_file(char *src_path, char *dest_path, char *filename){
	int rfd, wfd;
	struct stat statbuf;
	char *buf, *src_file, *dest_file;
	int n;

	src_file = (char *)malloc(sizeof(char) * (strlen(src_path) + strlen(filename) + 1));
	strcpy(src_file, src_path);
	strcat(src_file, "/");
	strcat(src_file, filename);

	dest_file = (char *)malloc(sizeof(char) * (strlen(dest_path) + strlen(filename) + 1));
	strcpy(dest_file, dest_path);
	strcat(dest_file, "/");
	strcat(dest_file, filename);

	printf("copy_file: %s %s\n", src_file, dest_file);

	if(stat(src_file, &statbuf) == -1){
		perror("stat");
	}

	buf = (char *) malloc(sizeof(char) * statbuf.st_size);
	if((rfd = open(src_file, O_RDONLY)) == -1){
		perror("open for read");
	}

	if((wfd = open(dest_file, O_WRONLY | O_CREAT, 0644)) == -1){
		perror("open for write");
	}

	while((n = read(rfd, buf, statbuf.st_size)) > 0){
		if(write(wfd, buf, n) != n){
			perror("write");
		}
	}
	if(buf != NULL){
		printf("free buf\n");
		free(buf);
	}
	close(rfd);
	close(wfd);
	return ;
}

/* dirent d_type 파일 타입

#define DT_UNKNOWN       0
#define DT_FIFO          1
#define DT_CHR           2
#define DT_DIR           4
#define DT_BLK           6
#define DT_REG           8
#define DT_LNK          10
#define DT_SOCK         12
#define DT_WHT          14

 */

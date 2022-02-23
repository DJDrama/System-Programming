#include <stdlib.h>
#include <stdio.h>

int main(){
	int ret;
	ret = remove("tmp.bbb");
	if(ret==-1){
		perror("Remove tmp.bbb");
		exit(1);
	}
	
	printf("Remove tmp.bbb success!!\n");
	
}

/* ./a.out --> Remove tmp.bbb: No such file or directory
* touch tmp.bbb
* ./a.out --> Remove tmp.bbb success!!
*/
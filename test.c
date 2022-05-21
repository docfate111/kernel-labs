#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
int main(int argc, char** argv){
	if(argc != 2){
		printf("Usage: %s [num]\n", argv[0]);
		return 1;
	}
	int fd = open("/dev/fibonacci", O_RDONLY);
	int num = atoi(argv[1]);
	if(lseek(fd, num, SEEK_SET)==-1){
		puts("lseek error");
	}
	printf("Fib(%d)=%d\n", num, read(fd, 0, 0));
	return 0;
}

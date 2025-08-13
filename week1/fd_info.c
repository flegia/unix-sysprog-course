#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUF_SIZE 10

int main(int argc, char* argv[]) {
	int fd;
	char buffer[BUF_SIZE];
	ssize_t nread;

	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		fprintf(stderr, "Error opening %s: %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	printf("File descriptor: %d\n", fd);
	nread = read(fd, buffer, BUF_SIZE);
	for (ssize_t i = 0; i < nread; i++) {
		printf("%02x", (unsigned char)buffer[i]);
	}
/*	if (write(STDOUT_FILENO, buffer, nread) != nread) {
		perror("write stdout");
		close(fd);
		exit(EXIT_FAILURE);
	}
*/	
	printf("\n");
	close(fd);
	return 0;
}

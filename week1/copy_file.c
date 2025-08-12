#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUF_SIZE 1024

int main(int argc, char* argv[]) {
	int output_dst;

	if ((argc != 2) && (argc != 3)) {
		fprintf(stderr, "Usage: %s <source> <dest>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (argc == 2) {
		output_dst=1;
	} else { output_dst=0;}

	int src = open(argv[1], O_RDONLY);
	if (src == -1) {
		perror("open source");
		exit(EXIT_FAILURE);
	}
	
	if (output_dst==0) {
	int dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dst == -1) {
		perror("open dest");
		close(src);
		exit(EXIT_FAILURE);
	}

	char buffer[BUF_SIZE];
	ssize_t bytes;
	while ((bytes = read(src, buffer, BUF_SIZE)) > 0) {
		if (write(dst, buffer, bytes) != bytes) {
			perror("write");
			close(src);
			close(dst);
			exit(EXIT_FAILURE);
		}
	}

	if (bytes == -1) {
		perror("read");

	close(src);
	close(dst);
	return 0;
	}
	} else {
		char buffer[BUF_SIZE];
		ssize_t bytes;
		while ((bytes = read(src,buffer,BUF_SIZE)) >0) {
			puts(buffer);
		}
		close(src);
		return 0;
	}

}

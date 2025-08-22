#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "globals.h"

#define NROOMS 10
#define NAMELENGTH 19

char namebuf[NAMELENGTH];

char* getoccupant(int roomno) {
	
        off_t offset;
        ssize_t nread;
        unsigned int empty_flag = 0;

        if ( fd == -1 && (fd = open(filename, O_RDONLY)) == -1) {
                printf("Couldn't open file error\n");
                return (NULL);
        }

        offset = (roomno - 1) * NAMELENGTH;

        if (lseek(fd, offset, SEEK_SET) == -1)
                return (NULL);

        if ((nread = read(fd, namebuf, NAMELENGTH)) <= 0)
                return (NULL);

        for (int i = 0; i<(nread-1); i++) {
                if ((namebuf[i] != ' ') && (namebuf[i] != '\n')) {
                        empty_flag = 1;
                }
        }

        if (empty_flag == 0)
                return(empty);
        namebuf[nread-1] = '\0';
        return(namebuf);
}

void setoccupant(int roomno, const char* name) {
	
	off_t offset;
	
	if ( fd == -1 && (fd = open(filename, O_RDWR)) == -1) {
		printf("Couldn't open file error\n");
		return;
	}

	offset = (roomno - 1) * NAMELENGTH;

	if (lseek(fd, offset, SEEK_SET) == -1)
		return;
	
	memset(namebuf, ' ', NAMELENGTH);
	namebuf[NAMELENGTH-1] = '\n';

	if (strlen(name) > 0) {
		strncpy(namebuf, name, NAMELENGTH - 1);
	}

	write(fd, namebuf, NAMELENGTH);
	return;
}

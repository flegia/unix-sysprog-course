#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "rooms.h"
#include "globals.h"

#define NROOMS 10
#define NAMELENGTH 19 

int main() {
	int j, cmp;
	char* p;
	int nfound,find;
	nfound = 0;

	int roomno = 5;
	const char name[NAMELENGTH] = "Alyssa Milano     \n";

	setoccupant(roomno, name);	
	

	for (j = 1; j <= NROOMS; j++) {
		p = getoccupant(j);
		cmp = strcmp(p,empty);
		if (cmp != 0)
			printf("Room %2d, %s\n", j, p);
		else if (cmp == 0) {
			printf("Room %2d: empty\n", j);
			if (nfound == 0) {
				find = j;
			}
			nfound++;
		}
		else
			printf("Error on room %d\n", j);
	}

	struct stat file_info;
	char perm_string[20] = "";


	if (stat(filename, &file_info) == 0) {
		cmp = file_info.st_mode;
		char cha[10] = "xwrxwrxwr";
		char temp[2];
		for (int k = 0; k < 9; k++) {
			temp[0] = cha[k];
			temp[1] = '\0';
			if (cmp & 1) {
				strcat(perm_string, temp);
			} else {
				strcat(perm_string, "-");
			}
			cmp = cmp >> 1;
		}
		strcat(perm_string, "-");

		printf("File: %s\n", filename);
		printf("Size: %lld bytes\n", (long long)file_info.st_size);
		printf("Last modified: %s", ctime(&file_info.st_mtime));
		printf("Permissions: ");
		for (int k = strlen(perm_string); k != 0; k--) {
			printf("%c", perm_string[k]);
		}
		printf("\n");
	} else {
		perror("stat");
	}

	printf("The first empty room is %d\n", find);
	printf("The number of empty rooms is %d\n", nfound);
	return 0;
}

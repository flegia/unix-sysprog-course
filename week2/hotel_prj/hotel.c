#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include "rooms.h"
#include "globals.h"

#define NROOMS 10
#define NAMELENGTH 19 

int main(int argc, char* argv[]) {

	if (argc < 2) {
		printf("Usage:\n");
		printf(" %s list\n", argv[0]);
		printf(" %s book ROOMNO NAME\n", argv[0]);
		printf(" %s free ROOMNO\n", argv[0]);
		printf(" %s info\n", argv[0]);
		return 1;
	}

	int j, cmp;
	char* p;
	int nfound,find;
	nfound = 0;

	if (strcmp(argv[1], "list") == 0) {
		//List rooms
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

		printf("The first empty room is %d\n", find);
		printf("The number of empty rooms is %d\n", nfound);
	
		return 0;
	}

	if (strcmp(argv[1], "book") == 0) {
		if (argc < 4) {
			fprintf(stderr, "Usage: %s book ROOMNO NAME\n", argv[0]);
			return 1;
		}
		int roomno = atoi(argv[2]);
		const char* name = argv[3];
		setoccupant(roomno, name);
		printf("Booked room %d for %s\n", roomno, name);
		return 0;
	}

	if (strcmp(argv[1], "free") == 0) {
		if (argc < 3) {
			fprintf(stderr, "Usage: %s free ROOMNO\n", argv[0]);
			return 1;
		}
		int roomno = atoi(argv[2]);
		setoccupant(roomno, "");
		printf("Room %d freed!\n", roomno);
		return 0;
	}

	if (strcmp(argv[1], "info") == 0) {
		if (argc < 2) {
			fprintf(stderr, "Usage: %s info\n");
			return 1;
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
		return 0;

	}

	fprintf(stderr, "Unknown command: %s\n", argv[1]);
	return 1;

	int roomno = 5;
	const char name[NAMELENGTH] = "Alyssa Milano     \n";

	setoccupant(roomno, name);	
	


}

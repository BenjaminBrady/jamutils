/* ls: list the contents of directories.
 *
 * This file is part of Jam Coreutils.
 *
 * Copyright (C) 2021 Benjamin Brady
 *
 * Jam Coreutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Jam Coreutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING. If not, see
 * <https://www.gnu.org/licenses/>. */
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void printdir(char *p);

int success = 0;
int aflag = 0;

inline void
printdir(char *p)
{
	int i, n;
	struct dirent **f;
	if ((n = scandir(p, &f, NULL, alphasort)) == -1) {
		perror("Error scanning directory");
		success = 1;
		return;
	};
	for (i = 0; i < n; i++) {
		if (f[i]->d_type == DT_DIR) {
			if (aflag || ((f[i]->d_name)[0] != '.')) {
				printf("%s\n", f[i]->d_name);
				free(f[i]);
			};
		};
	};
	for (i = 0; i < n; i++) {
		if (f[i]->d_type != DT_DIR) {
			if (aflag || ((f[i]->d_name)[0] != '.')) {
				printf("%s\n", f[i]->d_name);
				free(f[i]);
			};
		};
	};
	free(f);
}

int
main(int argc, char *argv[])
{
	int i;
	char *p;
	switch (argc) {
	case 1:
		printdir(".");
		break;
	case 2:
		if (!(strncmp(argv[1], "-a", 2))) {
			aflag = 1;
			printdir(".");
		} else {
			printdir(argv[1]);
		};
		break;
	default:
		if (!(strncmp(argv[1], "-a", 2))) aflag = 1;
		p = argv[1+aflag];
		if (aflag) {
			if (argc > 3) printf("%s:\n", p);
		} else printf("%s:\n", p);
		printdir(p);
		for (i = 2+aflag; i < argc; i++) {
			printf("\n");
			p = argv[i];
			printf("%s:\n", p);
			printdir(p);
		};
	};
	return success;
}

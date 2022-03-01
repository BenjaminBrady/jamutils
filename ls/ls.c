/* ls: list the contents of directories.
 *
 * This file is part of Jam Coreutils.
 *
 * Copyright (C) 2021-2022 Benjamin Brady <benjamin@benjaminbrady.ie>
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

#include "arg.h"

void printdir(char *p);

int success;
int aflag;
char *argv0;

inline void
printdir(char *p)
{
	int i, n;
	struct dirent **f;

	if ((n = scandir(p, &f, NULL, alphasort)) < 0) {
		fprintf(stderr, "scandir %s: ", p);
		perror(NULL);
		success = 1;
		return;
	};

	for (i = 0; i < n; i++) {
		if (f[i]->d_type == DT_DIR) {
			if (aflag || ((f[i]->d_name)[0] != '.')) {
				puts(f[i]->d_name);
				free(f[i]);
			};
		};
	};
	for (i = 0; i < n; i++) {
		if (f[i]->d_type != DT_DIR) {
			if (aflag || ((f[i]->d_name)[0] != '.')) {
				puts(f[i]->d_name);
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

	ARGBEGIN{
	case 'a': aflag = 1; break;
	default:
		fprintf(stderr, "usage: %s [-a]\n", argv0);
		return 1;
	}ARGEND;

	if (!argc) {
		printdir(".");
	} else {
		for (i = 0; i < argc; i++) {
			printf("%s:\n", argv[i]);
			printdir(argv[i]);
		};
	};

	return success;
}

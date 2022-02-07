/* pwd: print the absolute path to the current working directory.
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
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../arg.h"

char *argv0;
int Lflg = 1;

int
main(int argc, char *argv[])
{
	char *wd;
	struct stat dot, pwd;

	ARGBEGIN{
	case 'L': Lflg = 1; break;
	case 'P': Lflg = 0; break;
	default:
		fprintf(stderr, "usage: %s [-L|-P]\n", argv0);
		return 1;
	}ARGEND;

	if (Lflg) {
		wd = getenv("PWD");
		if (wd != NULL) {
			stat(".", &dot);
			if (stat(wd, &pwd) < 0) {
				perror("stat");
			} else if ((dot.st_ino == pwd.st_ino) &&
					(dot.st_dev == pwd.st_dev)) {
				/* TODO: apply cleanname */
				puts(wd);
				return 0;
			};
		} else {
			perror("getenv");
		};
	};

	wd = realpath(".", NULL);
	if (wd != NULL) {
		/* TODO: sift symlinks */
		puts(wd);
		free(wd);
	} else {
		perror("realpath");
		return 2;
	};

	return 0;
}

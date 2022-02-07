/* rmdir: remove the specified directories.
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
#include <libgen.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../arg.h"

char *argv0;
int pflg;

int
main(int argc, char *argv[])
{
	int err = 0;
	char *dir;

	ARGBEGIN{
	case 'p': pflg = 1; break;
	default:
		fprintf(stderr, "usage: %s [-p] dir...\n", argv0);
		return 1;
	}ARGEND;

	for (; *argv; argv++) {
		if (rmdir(*argv) < 0) {
			fprintf(stderr, "rmdir %s: ", *argv);
			perror(NULL);
			err = 2;
		} else if (pflg) for (dir = dirname(*argv); strcmp(dir, "/") &&
				strcmp(dir, "."); dir = dirname(dir)) {
			if (rmdir(dir) < 0) {
				fprintf(stderr, "rmdir %s: ", dir);
				perror(NULL);
				err = 2;
				break;
			};
		};
	};

	return err;
}

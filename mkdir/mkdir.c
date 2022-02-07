/* mkdir: make a directory at the specified location.
 *
 * This file is part of Jam Coreutils.
 *
 * Copyright (C) 2021 Benjamin Brady <benjamin@benjaminbrady.ie>
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
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../arg.h"

char *argv0;
int ret;
int pflg;

int
main(int argc, char *argv[])
{
	char *str, dirs[PATH_MAX];
	mode_t mode, mask, pmode;

	mask = umask(0);
	mode = (S_IRWXU | S_IRWXG | S_IRWXO) & ~mask;
	pmode = mode | S_IWUSR | S_IXUSR;

	ARGBEGIN{
	case 'p': pflg = 1; break;
	/* TODO: extend mode handling to all chmod strings */
	case 'm': if ((str = ARGF())) mode = strtol(str, NULL, 8); break;
	default:
		fprintf(stderr, "usage: %s [-p] [-m mode] dir...\n", argv0);
		return 1;
	}ARGEND;

	for (; *argv; argv++) {
		if (pflg) {
			str = *argv;
			strncpy(dirs, *argv, sizeof(dirs));
			for (str = dirs + (dirs[0] == '/'); *str; str++) {
				if (*str != '/') continue;
				*str = '\0';
				if ((mkdir(dirs, pmode) < 0) && (errno !=
							EEXIST)) {
					fprintf(stderr, "mkdir %s: ", dirs);
					perror(NULL);
					ret = 2;
				};
				*str = '/';
			};
		};
		if (mkdir(*argv, mode) < 0) {
			if ((errno == EEXIST) && pflg) continue;
			fprintf(stderr, "mkdir %s: ", *argv);
			perror(NULL);
			ret = 2;
		};
	};

	return ret;
}

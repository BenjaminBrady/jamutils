/* cmp: compare two files.
 *
 * This file is part of Jamutils.
 *
 * Copyright (C) 2021-2022 Benjamin Brady <benjamin@benjaminbrady.ie>
 *
 * Jamutils is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Jamutils is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Jamutils; see the file COPYING. If not, see <https://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arg.h"

#ifndef BUFSIZE
#define BUFSIZE BUFSIZ
#endif

int lflg, sflg;
char *argv0;

int
main(int argc, char *argv[])
{
	FILE *f, *g;
	char fbuf[BUFSIZE], gbuf[BUFSIZE];
	int ret = 0;

	ARGBEGIN{
	case 'l': lflg = 1; break; /* TODO: add -l and -s flags */
	case 's': sflg = 1; break;
	default:
usage:
		fprintf(stderr,
#ifdef OFFSETS
			"usage: %s [-l|-s] file1 file2 [offset1 [offset2]]\n",
#else
			"usage: %s [-l|-s] file1 file2\n",
#endif
			argv0);
		return 2;
	}ARGEND;
	if (argc < 2) goto usage;

	if (!(f = fopen(argv[0], "rb"))) {
		fprintf(stderr, "fopen %s: ", argv[0]);
		perror(NULL);
		return 3;
	};
	if (!(g = fopen(argv[1], "rb"))) {
		fprintf(stderr, "fopen %s: ", argv[1]);
		perror(NULL);
		return 3;
	};

#ifdef OFFSETS
	if (argc > 2) {
		fseek(f, atol(argv[2]), SEEK_SET);
		if (argc > 3) fseek(g, atol(argv[3]), SEEK_SET);
	};
#endif

	for (;;) {
		if (fgets(fbuf, BUFSIZE, f) != NULL) {
			if (fgets(gbuf, BUFSIZE, g) != NULL) {
				if (strncmp(fbuf, gbuf, BUFSIZE) != 0) {
					ret = 1;
					break;
				};
			} else {
				ret = 1;
				break;
			};
		} else {
			if (fgets(gbuf, BUFSIZE, g) != NULL) ret = 1;
			break;
		};
	};

	fclose(f);
	fclose(g);

	return ret;
}

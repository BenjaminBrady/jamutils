/* path: print the absolute path to files.
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
#ifdef CHECK_ACCESS
	#include <unistd.h>
#endif

#include "arg.h"

char *argv0;
int eflg;
int qflg;
int sflg;

int
main(int argc, char *argv[])
{
	char *path, *n;
	int ret = 0;
	FILE *stream = stderr;

	ARGBEGIN{
	case 'e': eflg = 1; break;
	case 'n': eflg = 0; break;
	case 'q': qflg = 1; break;
	case 's':
		if ((n = ARGF())) {
			switch (n[0]) {
			case 'o':
				sflg = 1;
				stream = stdout;
				break;
			case 'e':
				sflg = 1;
				stream = stderr;
			};
		};
		break;
	default:
		fprintf(stderr, "usage: %s [-enq] [-s stream] file...\n",
				argv0);
		return 1;
	}ARGEND;

	for (; *argv; argv++) {
#ifdef CHECK_ACCESS
		if (access(*argv, F_OK) < 0) {
			fprintf(stderr, "access %s: ", *argv);
			perror(NULL);
			ret = 2;
			continue;
		};
#endif
		path = realpath(*argv, NULL);
		if (path != NULL) {
			if (!qflg) fprintf(stream, "%s: ", *argv);
			if (eflg) {
				fputs(path, stdout);
				putchar('\0');
			} else puts(path);
			free(path);
		} else {
			fprintf(stderr, "realpath %s: ", *argv);
			perror(NULL);
			ret = 2;
		};
	};

	return ret;
}

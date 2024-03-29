/* strings: extract the printable strings from files.
 *
 * This file is part of Jamutils.
 *
 * Copyright (C) 2022 Benjamin Brady <benjamin@benjaminbrady.ie>
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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "arg.h"

#ifndef STRINGS_WRAP_LINES
#define STRINGS_WRAP_LINES 0 /* Define this to wrap lines */
#endif
#ifndef BUFSIZE
#define BUFSIZE BUFSIZ
#endif

#define isascii(a) ((a >= ' ' && a < 0x7f) || a == '\t')

void extstr(int fd);

char *argv0;
size_t minchars = 4;
char *fmt = "%s";
int tflg;
int ret;

void
extstr(int fd)
{
	char c, buf[BUFSIZE];
	size_t i = 0, j = 0, n = 0;

	while (read(fd, (void *) &c, sizeof(c)) > 0) {
		if (isascii(c)) {
			if (j == 0) j = i;
			buf[n++] = c;
			if (n == BUFSIZE-1) {
				buf[n] = 0;
				if (tflg) {
					printf(fmt, j, buf);
				} else printf(fmt, buf);
				if (STRINGS_WRAP_LINES) puts(" ...");
				j = 0;
				n = 0;
			};
		} else {
			if (n >= minchars) {
				buf[n] = 0;
				if (tflg) {
					printf(fmt, j, buf);
				} else printf(fmt, buf);
				putchar('\n');
			};
			j = 0;
			n = 0;
		};
		i++;
	};

	if (n >= minchars) {
		buf[n] = 0;
		if (tflg) {
			printf(fmt, j, buf);
		} else printf(fmt, buf);
		putchar('\n');
	};
}

int
main(int argc, char *argv[])
{
	int fd;
	char *n;

	ARGBEGIN{
	case 'a': break;
	case 'n':
		if ((n = ARGF())) minchars = atoi(n);
		break;
	case 't':
		if ((n = ARGF())) {
			switch (n[0]) {
			case 'd':
				tflg = 1;
				fmt = "%d %s";
				break;
			case 'o':
				tflg = 1;
				fmt = "%o %s";
				break;
			case 'x':
				tflg = 1;
				fmt = "%x %s";
				break;
			default: goto usage;
			};
		};
		break;
	default:
usage:
		fprintf(stderr,
			"usage: %s [-a] [-t format] [-n number] [file...]\n",
			argv0);
		return 1;
	}ARGEND;
	if (minchars < 1) minchars = 1;

	if (!argc) {
		extstr(STDIN_FILENO);
	} else for (; *argv; argv++) {
		if (!strcmp(*argv, "-")) {
			extstr(STDIN_FILENO);
		} else {
			if ((fd = open(*argv, O_RDONLY)) < 0) {
				fprintf(stderr, "open %s: ", *argv);
				perror(NULL);
				ret = 2;
			} else {
				extstr(fd);
				close(fd);
			};
		};
	};

	return ret;
}

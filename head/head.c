/* head: print the first few lines of files.
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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h> /* For wide-character support, currently unused */
#include <wctype.h>
#include <sys/stat.h>

#include "arg.h"

void header(int fd, char *name);

long lines = 10L;
int ret;
char *argv0;

void
header(int fd, char *name)
{
	/* Using: wint_t, fgetwc, WEOF, fputwc, and L'\n' should work for
	 * wide-character support; however, fputwc() doesn't appear to
	 * successfully issue a wide character - a thread safety issue
	 * perhaps? */
	FILE *f;
	char c;
	long p = 0L;

	if ((f = fdopen(fd, "r")) == NULL) {
		fprintf(stderr, "%s: ", name);
		perror("fdopen");
		ret = 2;
		return;
	};

	while ((c = fgetc(f)) != EOF) {
		putchar(c);
		if (c == '\n') {
			p++;
			if (p >= lines) {
				fclose(f);
				return;
			};
		};
	};

	fclose(f);
}

int
main(int argc, char *argv[])
{
	int i, fd;
	char *in;

	ARGBEGIN{
	case 'n':
		if ((in = ARGF()) == NULL) goto usage;
		lines = atol(in);
		break;
	default:
usage:
		fprintf(stderr, "usage: %s [-n lines] [file...]\n", argv0);
		return 1;
	}ARGEND;
	if (lines < 1) return 0;

	if (!argc) {
		header(STDIN_FILENO, "<stdin>");
	} else if (argc == 1) {
		if (!strcmp(argv[0], "-")) {
			header(STDIN_FILENO, "<stdin>");
		} else {
			if ((fd = open(argv[0], O_RDONLY)) < 0) {
				fprintf(stderr, "open %s: ", argv[0]);
				perror(NULL);
				ret = 2;
			} else {
				header(fd, argv[0]);
				close(fd);
			};
		};
	} else for (i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "-")) {
			puts("==> <stdin> <==");
			header(STDIN_FILENO, "<stdin>");
		} else {
			if ((fd = open(argv[i], O_RDONLY)) < 0) {
				fprintf(stderr, "open %s: ", argv[i]);
				perror(NULL);
				ret = 2;
			} else {
				printf("==> %s <==\n", argv[i]);
				header(fd, argv[i]);
				close(fd);
			};
		};

		if (i != argc-1) putchar('\n');
	};

	return ret;
}

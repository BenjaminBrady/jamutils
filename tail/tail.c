/* tail: print the last few lines of files.
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
#include <wchar.h> /* Wide-character support proves tumultuous. See head.c */
#include <wctype.h>
#include <sys/stat.h>

#include "arg.h"

void footer(int fd, char *name);

long lines = 10L;
int ret;
char *argv0;
int cflg, fflg;

void
footer(int fd, char *name)
{
	FILE *f;
	long p, nl = 0L;
	wint_t c;

	if ((f = fdopen(fd, "rb")) == NULL) {
		fprintf(stderr, "%s: ", name);
		perror("fdopen");
		ret = 2;
		return;
	};

	/* FIXME: cannot seek on certain streams, e.g. stdin */
	if (fseek(f, 0, SEEK_END) < 0) {
		perror("fseek");
		ret = 2;
		return;
	};
	if (cflg) {
		for (p = ftell(f); p >= 0; p--) {
			if (fseek(f, p, SEEK_SET) < 0) {
				perror("fseek");
				ret = 2;
				return;
			};
			fgetwc(f);
			nl++;
			if (nl > lines) goto print;
		};
	} else {
		for (p = ftell(f); p >= 0; p--) {
			if (fseek(f, p, SEEK_SET) < 0) {
				perror("fseek");
				ret = 2;
				return;
			};
			if (fgetwc(f) == L'\n') {
				nl++;
				if (nl > lines) goto print;
			};
		};
	};
	fseek(f, 0L, SEEK_SET);
print:
	while ((c = fgetwc(f)) != WEOF) fputwc(c, stdout);

	fclose(f);
}

int
main(int argc, char *argv[])
{
	int fd;
	char *in;

	ARGBEGIN{
	case 'c':
		cflg = 1;
		goto input;
	case 'f': fflg = 1; break; /* TODO: implement -f */
	case 'n':
		cflg = 0;
input:
		if ((in = ARGF()) == NULL) goto usage;
		lines = atol(in);
		break;
	default:
usage:
		fprintf(stderr,
			"usage: %s [-f] [-c number|-n number] [file]\n",
			argv0);
		return 1;
	}ARGEND;
	if (lines < 1) return 0;

	if (!(argc && strcmp(*argv, "-"))) {
		footer(STDIN_FILENO, "<stdin>");
	} else {
		if ((fd = open(*argv, O_RDONLY)) < 0) {
			fprintf(stderr, "open %s: ", *argv);
			perror(NULL);
			ret = 2;
		} else {
			footer(fd, *argv);
			close(fd);
		};
	};

	return ret;
}

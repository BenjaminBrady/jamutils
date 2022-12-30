/* wc: print byte, line, and word counts of files.
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
#include <wchar.h>
#include <wctype.h>
#include <sys/stat.h>

#include "arg.h"

#define _(a) (a)
#define c_count (1 << 0)
#define l_count (1 << 1)
#define w_count (1 << 2)

void count(int fd, char *name);

int ret;
int flag;
int mflg;
long tc, tl, tw;
char *argv0;

void
count(int fd, char *name)
{
	FILE *f;
	int wsf = 0;
	long c = 0L;
	long l = 0L;
	long w = 0L;
	wint_t ch;
	long b;

	if ((f = fdopen(fd, "rb")) == NULL) {
		fprintf(stderr, "%s: ", name);
		perror("fdopen");
		ret = 2;
		return;
	};

	while ((ch = fgetwc(f)) != WEOF) {
		if (iswspace(ch)) {
			if (ch == L'\n') l++;
			if (wsf == 1) {
				wsf = 0;
				w++;
			};
		} else wsf = 1;
		c++;
	};

	if (!mflg && (fd != 0)) {
		if ((b = ftell(f)) < 0) {
			fprintf(stderr, "%s: ", name);
			perror("ftell");
			ret = 2;
			b = c;
		};
		c = b;
	};

	tc += c;
	tl += l;
	tw += w;

	if (flag & l_count) printf("%ld ", l);
	if (flag & w_count) printf("%ld ", w);
	if (flag & c_count) printf("%ld ", c);
	if (flag == 0) printf("%ld %ld %ld ", l, w, c);
	puts(name);
}

int
main(int argc, char *argv[])
{
	int i, fd;

	ARGBEGIN{
	case 'c': flag |= c_count; mflg = 0; break;
	case 'l': flag |= l_count; break;
	case 'm': flag |= c_count; mflg = 1; break;
	case 'w': flag |= w_count; break;
	default:
		fprintf(stderr, "usage: %s [-c|-m] [-lw] [file...]\n", argv0);
		return 1;
	}ARGEND;

	if (!argc) {
		count(STDIN_FILENO, "<stdin>");
	} else {
		for (i = 0; i < argc; i++) {
			if (!strcmp(argv[i], "-")) {
				count(STDIN_FILENO, "<stdin>");
			} else {
				if ((fd = open(argv[i], O_RDONLY)) < 0) {
					fprintf(stderr, "open %s: ", argv[i]);
					perror(NULL);
					ret = 2;
				} else {
					count(fd, argv[i]);
					close(fd);
				};
			};
		};

		if (argc > 1) {
			if (flag & l_count) printf("%ld ", tl);
			if (flag & w_count) printf("%ld ", tw);
			if (flag & c_count) printf("%ld ", tc);
			if (flag == 0) printf("%ld %ld %ld ", tl, tw, tc);
			fputs(_("total\n"), stdout);
		};
	};

	return ret;
}

/* wc: print various counts of file attributes (bytes, lines, etc.).
 *
 * This file is part of Jam Coreutils.
 *
 * Copyright (C) 2021 Benjamin Brady
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
#include <string.h>

#include "jam.h"

long tl = 0;
long tw = 0;
long tb = 0;
long tll = 0;

int
main(int argc, char *argv[])
{
	int i, success, wsf;
	long l, w, b, ll, mll;
	char c;
	FILE *f;
	if (argc < 2) {
		printf("Usage: wc file (...)\n");
		return 1;
	};
	if (strncmp(argv[1], "-h", 2) == 0) {
		printf("file: lines, words, bytes, line length\n");
		argv++;
		argc--;
	};
	success = 0;
	for (i = 1; i < argc; i++) {
		if (!(f = fopen(argv[i], "r"))) {
			success = 2;
			perror("Opening file");
		} else {
			l = w = b = ll = mll = 0L;
			wsf = 0;
			while ((c = fgetc(f)) != EOF) {
				switch (c) {
				case '\n':
					if (ll > mll) mll = ll;
					ll = 0;
					l++;
					goto sp;
				case '\t': /* FALLTHROUGH */
					ll += 7 - (ll % 8);
				case '\v':
				case '\f':
				case '\r':
				case  ' ':
					ll++;
sp:
					if (wsf == 1) {
						wsf = 0;
						w++;
					};
					break;
				default:
					ll++;
					wsf = 1;
				};
			};
			if (ll > mll) mll = ll;
			b = ftell(f);
			fclose(f);
			printf("%s: %li, %li, %li, %li\n",
					argv[i], l, w, b, mll);
			tl += l;
			tw += w;
			tb += b;
			if (mll > tll) tll = mll;
		};
	};
	if (argc > 2)
		printf("total: %li, %li, %li, %li\n", tl, tw, tb, tll);
	return success;
}

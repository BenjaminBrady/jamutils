/* cal: print a calendar.
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
#include <time.h>

#include "arg.h"

char *argv0;

const char *months[] = {
	"January", "February", "March", "April",
	"May", "June", "July", "August",
	"September", "October", "November", "December",
};

const char *days = "Mo Tu We Th Fr Sa Su";

int len[] = {
	31, 28, 31, 30,
	31, 30, 31, 31,
	30, 31, 30, 31,
};

int namelen[] = {
	7, 8, 5, 5,
	3, 4, 4, 6,
	9, 7, 8, 8,
};

int
main(int argc, char *argv[])
{
	int mon, yr, i, length, first, space, yrlen;
	time_t t;
	struct tm *n;
	double in;

	ARGBEGIN{
	default:
usage:
		fprintf(stderr, "usage: %s [[month] year]\n", argv0);
		return 1;
	}ARGEND;
	switch (argc) {
	case 1:
		/* Print the year */
		in = atof(argv[0]);
		if (in < 0E0 || in > 9.999E3) goto usage;
		yr = (int) in;
		/* TODO: Print the year. We print the month here for now. */
		t = time(NULL);
		n = localtime(&t);
		mon = n->tm_mon;
		break;

	/* Print the month */
	case 0:
		t = time(NULL);
		n = localtime(&t);
		yr = n->tm_year + 1900;
		mon = n->tm_mon;
		break;
	default:
		in = atof(argv[1]);
		if (in < 0E0 || in > 9.999E3) goto usage;
		yr = (int) in;
		in = atof(argv[0]);
		if (in < 1 || in > 12) goto usage;
		mon = ((int) in) - 1;
	};

	if (yr % 4 == 0) {
		if (yr % 100 == 0) {
			if (yr % 400 == 0) len[1] = 29;
		} else len[1] = 29;
	};
	length = len[mon];

	if (yr >= 1000) {
		yrlen = 4;
	} else if (yr >= 100) {
		yrlen = 3;
	} else if (yr >= 10) {
		yrlen = 2;
	} else yrlen = 1;
	space = (20 - namelen[mon] - yrlen) >> 1;
	for (i = 0; i < space; i++) putchar(' ');
	printf("%s %d\n%s\n ", months[mon], yr, days);

	first = 4 + yr + (yr+3)/4;
	if (yr >= 1752) {
		if (yr == 1752) {
			if (mon == 8) {
				fputs("   1  2 ", stdout);
				for (i = 14; i < 31; i++) {
					printf("%d", i);
					switch (i) {
					case 14: /* Fallthrough */ case 15:
					case 16: case 18: case 19: case 20:
					case 21: case 22: case 23: case 25:
					case 26: case 27: case 28: case 29:
					case 30:
						putchar(' ');
						break;
					case 17: /* Fallthrough */ case 24:
						putchar('\n');
						break;
					};
				};
				putchar('\n');
				return 0;
			};
			if (mon > 8) len[8] = 19;
		};

		first += 3;
		if (yr > 1800) {
			first -= (yr-1701)/100;
			first += (yr-1601)/400;
		};
	};
	for (i = 0; i < mon; i++) first += len[i];
	first = (first + 6) % 7;
	for (i = 0; i < first; i++) fputs("   ", stdout);

	for (i = 1; i <= length; i++) {
		printf("%d", i);
		if ((i + first) % 7 == 0) {
			putchar('\n');
			if (i < 9) putchar(' ');
		} else {
			putchar(' ');
			if (i < 9) putchar(' ');
		};
	};
	if ((i + first) % 7 != 1) putchar('\n');

	return 0;
}

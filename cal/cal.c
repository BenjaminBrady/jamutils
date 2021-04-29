/* cal: print a calendar.
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *months[] = {
	"January", "February", "March", "April",
	"May", "June", "July", "August",
	"September", "October", "November", "December",
};

const char days[] = "Mo Tu We Th Fr Sa Su";

int len[] = {
	31, 28, 31, 30,
	31, 30, 31, 31,
	30, 31, 30, 31,
};

int
main(int argc, char *argv[])
{
	int mon, yr, i, length, first;
	time_t t;
	struct tm *n;
	t = time(NULL);
	n = localtime(&t);
	switch (argc) {
	case 1:
		mon = n->tm_mon;
		yr = n->tm_year + 1900;
		break;
	case 2:
		mon = atoi(argv[1]) - 1;
		yr = n->tm_year + 1900;
		break;
	default:
		mon = atoi(argv[1]) - 1;
		yr = atoi(argv[2]);
	};
	if (mon < 0 || mon > 11 || yr < 0 || yr > 99999) {
		printf("Usage: cal [month] [year]\n");
		return 1;
	};
	if (yr % 4 == 0) {
		if (yr % 100 == 0) {
			if (yr % 400 == 0) len[1] = 29;
		} else len[1] = 29;
	};
	length = len[mon];
	printf("    %s %d\n%s\n ", months[mon], yr, days);
	first = 4 + yr + (yr+3)/4;
	if (yr >= 1752) {
		if (yr == 1752) {
			if (mon == 8) {
				printf("   1  2 ");
				for (i = 14; i < 31; i++) {
					printf("%d ", i);
					if (i == 17 || i == 24) printf("\n");
				};
				printf("\n");
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
	first = (first - 1) % 7;
	for (i = 0; i < first; i++) printf("   ");
	for (i = 1; i <= length; i++) {
		printf("%d", i);
		if ((i + first) % 7 == 0) {
			printf("\n");
			if (i < 9) printf(" ");
		} else {
			printf(" ");
			if (i < 9) printf(" ");
		};
	};
	if ((i + first) % 7 != 1) printf("\n");
	return 0;
}

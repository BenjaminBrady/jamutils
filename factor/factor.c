/* factor: print the prime factorisation of each argument.
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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "arg.h"

void factor(double n);

char *argv0;

double wheel[] = {
	2,10, 2, 4, 2, 4, 6, 2, 6, 4,
	2, 4, 6, 6, 2, 6, 4, 2, 6, 4,
	6, 8, 4, 2, 4, 2, 4, 8, 6, 4,
	6, 2, 4, 6, 2, 6, 6, 4, 2, 4,
	6, 2, 6, 4, 2, 4, 2,10,
};

void
factor(double n)
{
	int i;
	double rm, d, s;

	printf("%.0lf:", n);

	if (n <= 0) {
		if (n == 0) {
			puts(" 0");
			return;
		};
		fputs(" -1", stdout);
		n *= -1E0;
	};

	s = sqrt(n) + 1;
	while (modf(n/2, &rm) == 0) {
		fputs(" 2", stdout);
		n = rm;
		s = sqrt(n) + 1;
	};
	while (modf(n/3, &rm) == 0) {
		fputs(" 3", stdout);
		n = rm;
		s = sqrt(n) + 1;
	};
	while (modf(n/5, &rm) == 0) {
		fputs(" 5", stdout);
		n = rm;
		s = sqrt(n) + 1;
	};
	while (modf(n/7, &rm) == 0) {
		fputs(" 7", stdout);
		n = rm;
		s = sqrt(n) + 1;
	};

	for (d = 1, i = 1; d <= s; i++) {
		d += wheel[i%48];
		while (modf(n/d, &rm) == 0) {
			printf(" %.0lf", d);
			n = rm;
			s = sqrt(n) + 1;
		};
	};

	if (n > 1) printf(" %.0lf", n);

	putchar('\n');
}

int
main(int argc, char *argv[])
{
	double in;
	double sup = 9.007199254740992E15; /* Maximum int-accurate double */

	ARGBEGIN{
	ARGNUM: argv[0]--; goto neg;
	default:
		fprintf(stderr, "usage: %s int...\n", argv0);
		return 1;
	}ARGEND;
neg:

	for (; *argv; argv++) {
		in = atof(*argv);
		if (in > -sup && in < sup) {
			factor(in);
		} else fputs("Limits exceeded\n", stderr);
	};

	return 0;
}

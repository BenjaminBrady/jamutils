/* factor: print the prime factorisation of inputted integers.
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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "jam.h"

void factor(double n);

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
	if (n == 0) return;
	s = sqrt(n) + 1;
	while (modf(n/2, &rm) == 0) {
		printf(" 2");
		n = rm;
		s = sqrt(n) + 1;
	};
	while (modf(n/3, &rm) == 0) {
		printf(" 3");
		n = rm;
		s = sqrt(n) + 1;
	};
	while (modf(n/5, &rm) == 0) {
		printf(" 5");
		n = rm;
		s = sqrt(n) + 1;
	};
	while (modf(n/7, &rm) == 0) {
		printf(" 7");
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
	printf("\n");
}

int
main(int argc, char *argv[])
{
	int i;
	double n;
	if (argc < 2) {
		printf("Usage: factor int (...)\n");
		return 1;
	};
	for (i = 1; i < argc; i++) {
		n = atof(argv[i]);
		if (n > 0) factor(n);
	};
	return 0;
}

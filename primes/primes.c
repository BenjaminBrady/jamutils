/* primes: print prime numbers in a range.
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

#define _(a) (a)

void transform(double lb, long k);

int pt[50] = {
	2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
	31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
	73, 79, 83, 89, 97, 101,103,107,109,113,
	127,131,137,139,149,151,157,163,167,173,
	179,181,191,193,197,199,211,223,227,229,
};

char table[1000];

unsigned char bittab[] = {
	1, 2, 4, 8, 16, 32, 64, 128,
};

double wheel[48] = {
       10, 2, 4, 2, 4, 6, 2, 6, 4, 2,
	4, 6, 6, 2, 6, 4, 2, 6, 4, 6,
	8, 4, 2, 4, 2, 4, 8, 6, 4, 6,
	2, 4, 6, 2, 6, 6, 4, 2, 4, 6,
	2, 6, 4, 2, 4, 2,10, 2,
};

void
transform(double lb, long k)
{
	double t1;
	long j;

	modf(lb/k, &t1);
	j = k*t1 - lb;
	if (j < 0) j += k;
	for (; j < 1000*8; j += k) table[j>>3] |= bittab[j&07];
}

int
main(int argc, char *argv[])
{
	int i;
	double lb, ub, temp, v, k;
	double sup = 9.007199254740992E15; /* Maximum int-accurate double */

	if (argc < 2) {
		fprintf(stderr, "usage: %s [starting [ending]]\n", argv[0]);
		return 1;
	};

	lb = atof(argv[1]);
	ub = sup;
	if (argc > 2) {
		ub = atof(argv[2]);
		if (ub < lb) return 0;
		if (ub > sup) {
limits:

			fputs(_("Limits exceeded\n"), stderr);
			return 1;
		};
	};
	if (lb < 1 || lb > sup) goto limits;
	if (lb < 230) {
		for (i = 0; i < 50; i++) {
			if (pt[i] < lb) continue;
			if (pt[i] > ub) return 0;
			printf("%d\n", pt[i]);
			if (ub >= sup) return 0;
		};
		lb = 230;
	};

	modf(lb/2, &temp);
	lb = 2E0 * temp + 1;
	for (;;) {
		for (i = 0; i < 1000; i++) table[i] = 0;
		/* Run a prime sieve */
		v = sqrt(lb + 8 * 1000);
		transform(lb, 3);
		transform(lb, 5);
		transform(lb, 7);
		for (i = 0, k = 11; k <= v; i++, k += wheel[i % 48])
			transform(lb, k);
		for (i = 0; i < 1000*8; i += 2) {
			if (table[i>>3] & bittab[i&07]) continue;
			temp = lb + i;
			if (temp > ub) return 0;
			printf("%.0lf\n", temp);
			if (ub >= sup) return 0;
		};
		lb += 1000*8;
	};

	return 0;
}

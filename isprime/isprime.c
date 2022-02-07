/* isprime: determine whether or not each argument is a prime number.
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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void isprime(double p);

int primes[] = {
	7, 11, 13, 17, 19, 23, 29, 31,
};

void
isprime(double p)
{
	size_t i, j, k;
	unsigned long long l, r;
	
	l = (unsigned long long) sqrt(p);
	r = (unsigned long long) p;
	if (p < 2) goto notprime;
	if (r == 2 || r == 3 || r == 5) goto isprime;
	if (r % 2 == 0 || r % 3 == 0 || r % 5 == 0) goto notprime;

	for (i = 0; i < l; i += 30) {
		for (j = 0; j < 8; j++) {
			k = primes[j] + i;
			if (k > l) break;
			if (r % k == 0) goto notprime;
		};
	};
isprime:
	printf("%.0lf is a prime number\n", p);
	return;
notprime:
	printf("%.0lf is not a prime number\n", p);
}

int
main(int argc, char *argv[])
{
	int i;
	double t, sup = 9.007199254740992E15; /* max integer-accurate double */

	if (argc < 2) {
		fputs("usage: isprime int ...\n", stderr);
		return 1;
	};

	for (i = 1; i < argc; i++) {
		t = atof(argv[i]);
		if (t >= sup || t <= -sup) {
			fputs("Limits exceeded\n", stdout);
		} else {
			isprime(t);
		};
	};
	return 0;
}

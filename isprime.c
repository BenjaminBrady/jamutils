/* isprime: determine whether or not each input is a prime number.
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

void isprime(int p);

int primes[] = {
	7, 11, 13, 17, 19, 23, 29, 31,
};

void
isprime(int p)
{
	int l, i, j, k;
	if (p < 2) goto notprime;
	l = (int) sqrt(p);
	if (p == 2 || p == 3 || p == 5) goto isprime;
	if (p % 2 == 0 || p % 3 == 0 || p % 5 == 0) goto notprime;
	for (i = 0; i < l; i += 30) {
		for (j = 0; j < 8; j++) {
			k = primes[j];
			if (k > l) break;
			if (p % (i+k) == 0) goto notprime;
		};
	};
isprime:
	printf("%d is a prime number\n", p);
	return;
notprime:
	printf("%d is not a prime number\n", p);
}

int
main(int argc, char *argv[])
{
	int i;
	if (argc < 2) {
		printf("Usage: isprime int (...)\n");
		return 1;
	};
	for (i = 1; i < argc; i++) isprime(atoi(argv[i]));
	return 0;
}

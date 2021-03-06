/* factorial: print the factorial of the inputed integers.
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

long double factorial(long double z, long double w);

int big = 1754;

long double
factorial(long double z, long double w)
{
	if (z == 0) return w;
	return factorial(z-1, z*w);
}

int
main(int argc, char *argv[])
{
	int i, z;
	if (argc < 2) {
		printf("Usage factorial int (...)\n");
		return 1;
	};
	for (i = 1; i < argc; i++) {
		z = atoi(argv[i]);
		if (z < 0) {
			printf("Divergent\n");
			continue;
		};
		if (z > big) {
			printf("Limits exceeded\n");
			continue;
		};
		printf("%.16Lg\n", factorial(z, 1E0));
	};
	return 0;
}

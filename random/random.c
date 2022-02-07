/* random: print the output of a pseudo random number generator.
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

#include "../arg.h"

char *argv0;
int hflg;

int
main(int argc, char *argv[])
{
	int i;
	ARGBEGIN{
	case 'h':	hflg = 1; break;
	default:
			fputs("Usage: random [-h] [int]\n", stderr);
			return 1;
	}ARGEND;
	srand(time(0));
	if (hflg) printf("Returns random numbers in [0,%d]\n", RAND_MAX);
	argc ? (i = atoi(argv[0])) : (i = 1);
	while (i--) printf("%d\n", rand());
	return 0;
}

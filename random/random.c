/* random: print the output of a pseudo random number generator.
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
#include <stdlib.h>
#include <string.h>
#include <time.h>

int
main(int argc, char *argv[])
{
	int i, l, cflag;
	srand(time(0));
	l = 1;
	switch (argc) {
	case 1:
		l = 1;
		break;
	case 2:
		if (strncmp(argv[1], "-c", 2) == 0) {
			printf("Returns random numbers in [0,%d]\n",
					RAND_MAX);
			l = 1;
		} else l = atoi(argv[1]);
		break;
	default:
		cflag = 0;
		if (strncmp(argv[1], "-c", 2) == 0) {
			printf("Returns random numbers in [0,%d]\n",
					RAND_MAX);
			cflag = 1;
		};
		l = atoi(argv[1+cflag]);
	};
	for (i = 0; i < l; i++) printf("%d\n", rand());
	return 0;
}

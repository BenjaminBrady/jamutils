/* average: average the inputted set.
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

#include "jam.h"

int
main(int argc, char *argv[])
{
	int i;
	double sum;
	if (argc < 2) {
		printf("Usage: average doubles (...)\n");
		return 1;
	};
	sum = 0;
	for (i = 1; i < argc; i++) {
		sum += atof(argv[i]);
	};
	sum /= argc-1;
	printf("%.16g\n", sum);
	return 0;
}

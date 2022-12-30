/* min: print the minimum of the inputted set.
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
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	int i;
	double min, t;

	if (argc < 2) {
		fprintf(stderr, "usage: %s set\n", argv[0]);
		return 1;
	};

	min = atof(argv[1]);
	for (i = 2; i < argc; i++) {
		t = atof(argv[i]);
		if (min > t) min = t;
	};
	printf("%.16g\n", min);

	return 0;
}

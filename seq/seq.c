/* seq: print values of a sequence of numbers.
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

int
main(int argc, char *argv[])
{
	double s, e, c, i;
	switch(argc) {
	case 1:
		printf("Usage: seq [starting [increment]] ending\n");
		return 1;
	case 2:
		s = 1;
		e = atof(argv[1]);
		c = 1;
		break;
	case 3:
		s = atof(argv[1]);
		e = atof(argv[2]);
		c = 1;
		break;
	default:
		s = atof(argv[1]);
		e = atof(argv[3]);
		c = atof(argv[2]);
	};
	if (c == 0) {
		printf("Invalid increment value!\n");
		return 1;
	};
	if (s <= e) {
		if (c < 0) return 0;
		for (i = s; i <= e; i += c) printf("%.16g\n", i);
	} else {
		if (c > 0) return 0;
		for (i = s; i >= e; i += c) printf("%.16g\n", i);
	};
	return 0;
}

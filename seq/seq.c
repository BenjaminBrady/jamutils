/* seq: print a linear sequence.
 * 
 * This file is part of Jam Coreutils.
 *
 * Copyright (C) 2021-2022 Benjamin Brady <benjamin@benjaminbrady.ie>
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

#include "../arg.h"

#define _(a) (a)

char *argv0;
char *fmt = "%.16G\n";

int
main(int argc, char *argv[])
{
	double s, e, c, i;

	ARGBEGIN{
	case 'f':
		if ((fmt = ARGF()) == NULL) goto usage;
		break;
	default:
		goto neg;
	}ARGEND;
neg:

	switch (argc) {
	case 0:
usage:
		fprintf(stderr, _("usage: %s [start [increment]] end\n"),
				argv0);
		return 1;
	case 1:
		s = 1E0;
		e = atof(argv[0]);
		c = 1E0;
		break;
	case 2:
		s = atof(argv[0]);
		e = atof(argv[1]);
		c = 1E0;
		break;
	default:
		s = atof(argv[0]);
		e = atof(argv[2]);
		c = atof(argv[1]);
	};

	if (c == 0) goto usage;

	if (s <= e) {
		if (c < 0) return 0;
		for (i = s; i <= e; i += c) printf(fmt, i);
	} else {
		if (c > 0) return 0;
		for (i = s; i >= e; i += c) printf(fmt, i);
	};

	return 0;
}

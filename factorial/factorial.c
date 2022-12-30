/* factorial: print the factorial of each argument.
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

#include "arg.h"

#define _(a) (a)

long double factorial(long double z, long double w);

char *argv0;
char *fmt = "%.16LG\n";
int big = 1754;

long double
factorial(long double z, long double w)
{
	return (z == 0) ? w : factorial(z-1, z*w);
}

int
main(int argc, char *argv[])
{
	int z;

	ARGBEGIN{
	case 'f':
		if ((fmt = ARGF()) == NULL) goto usage;
		break;
	ARGNUM: argv[0]--; goto neg;
	default:
usage:
		fprintf(stderr, "usage: %s [-f fmt] int...\n", argv0);
		return 1;
	}ARGEND;
neg:

	for (; *argv; argv++) {
		z = atoi(*argv);

		if (z < 0) {
			fputs(_("Divergent\n"), stderr);
			continue;
		};
		if (z > big) {
			fputs(_("Limits exceeded\n"), stderr);
			continue;
		};

		printf(fmt, factorial(z, 1E0));
	};

	return 0;
}

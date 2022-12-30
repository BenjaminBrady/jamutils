/* sleep: have the current thread sleep.
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
#include <unistd.h>

#include "arg.h"

char *argv0;

int
main(int argc, char *argv[])
{
	unsigned long s;

	ARGBEGIN{
	default:
usage:
		fprintf(stderr, "usage: %s time\n", argv0);
		return 1;
	}ARGEND;
	if (!argc) goto usage;

	s = strtoul(*argv, NULL, 10);
	sleep((unsigned) s);

	return 0;
}

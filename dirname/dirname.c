/* dirname: return the directory portion of a pathname.
 *
 * This file is part of Jamutils.
 *
 * Copyright (C) 2022 Benjamin Brady <benjamin@benjaminbrady.ie>
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
#include <libgen.h>
#include <stdio.h>

#include "arg.h"

char *argv0;

int
main(int argc, char *argv[])
{
	ARGBEGIN{
	default:
usage:
		fprintf(stderr, "usage: %s\n", argv0);
		return 1;
	}ARGEND;
	if (!argc) goto usage;

#ifdef MULTIPLE_DIRECTORIES
	for (; *argv; argv++)
#endif
		puts(dirname(*argv));

	return 0;
}

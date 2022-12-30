/* echo: write arguments to standard output.
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
#include <string.h>

int
main(int argc, char *argv[])
{
	int i;
	size_t l = 0;
	char *s = NULL, *p;

	if (argc < 2) return 0;
	for (i = 1; i < argc; i++) {
		l += strlen(argv[i])+1; /* arg + (' ' or NUL) */
	};
	if (!(s = (char *) malloc(l))) {
		perror("malloc");
		return 1;
	};
	p = s;
	/* TODO: handle supported operands */

	for (i = 1; i < argc; i++) {
		strcpy(s, argv[i]);
		s += strlen(s);
		if (i == argc-1) {
			*s++ = 0;
		} else *s++ = ' ';
	};

	puts(p);

	return 0;
}

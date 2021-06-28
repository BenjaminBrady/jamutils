/* pbd: print the name of the current working directory.
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
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *realpath(const char *restrict path, char *restrict resolved_path);

int
main(void)
{
	char *d;
	d = realpath(".", NULL);
	d = strrchr(d, '/');
	if (d != NULL) {
		d++;
		if (strncmp(d, "", 1) == 0) d = "/";
		printf("%s\n", d);
		return 0;
	};
	return 1;
}

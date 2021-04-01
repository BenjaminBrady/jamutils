/* basename: print the name of inputted files without preceeding path.
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
#include <string.h>

#include "jam.h"

int
main(int argc, char *argv[])
{
	int i;
	char *bn;
	if (argc < 2) {
		printf("Usage: basename file (...)\n");
		return 1;
	};
	for (i = 1; i < argc; i++) {
		bn = strrchr(argv[i], '/');
		if (bn != NULL) bn++;
		printf("%s\n", bn);
	};
	return 0;
}

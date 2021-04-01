/* rm: remove the specified files.
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

#include "jam.h"

int success = 0;

int
main(int argc, char *argv[])
{
	int i;
	if (argc < 2) {
		printf("Usage: rm file (...)\n");
		return 1;
	};
	for (i = 1; i < argc; i++) {
		if (!(remove(argv[i]) == 0)) {
			perror("Cannot remove file");
			success = 1;
		} else printf("removed '%s'\n", argv[i]);
	};
	return success;
}

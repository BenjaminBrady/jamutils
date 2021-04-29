/* path: print the absolute path to each inputted file.
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
#include <unistd.h>

char *realpath(const char *restrict path, char *restrict resolved_path);

int
main(int argc, char *argv[])
{
	int i;
	if (argc < 2) {
		printf("Usage: path file (...)\n");
		return 1;
	};
	for (i = 1; i < argc; i++) {
		if (access(argv[i], F_OK) == 0) {
			printf("%s\n", realpath(argv[i], NULL));
		} else perror("Error accessing file");
	};
	return 0;
}

/* cmp: compare input files and check if different.
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
#include <stdlib.h>
#include <string.h>

#include "jam.h"

int iso = 0;

int
main(int argc, char *argv[])
{
	FILE *f, *g;
	char bufa[8192], bufb[8192];
	if (argc < 3) {
		printf("Usage cmp file1 file2 [offset1 [offset2]]\n");
		return 2;
	};
	if (!(f = fopen(argv[1], "rb"))) {
		perror("Opening file1");
		return 2;
	};
	if (!(g = fopen(argv[2], "rb"))) {
		perror("Opening file2");
		return 2;
	};
	if (argc > 3) fseek(f, atol(argv[3]), SEEK_SET);
	if (argc > 4) fseek(g, atol(argv[4]), SEEK_SET);
	/* Current bug: this will almost surely trip up on binary files
	 * when it reads control characters or coincidental newlines */
	for (;;) {
		if (fgets(bufa, 8192, f) != NULL) {
			if (fgets(bufb, 8192, g) != NULL)
				if (strncmp(bufa, bufb, 8192) != 0) {
					iso = 1;
					break;
				};
		} else {
			if (fgets(bufb, 8192, g) != NULL) iso = 1;
			break;
		};

	};
	fclose(f);
	fclose(g);
	return iso;
}

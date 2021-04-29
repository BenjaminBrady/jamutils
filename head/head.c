/* head: output the first few lines (10 by default) of specified files.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	char buf[8192];
	FILE *f;
	int i, nflag, success, multi;
	unsigned long j, big;
	if (argc < 2) {
usage:
		printf("Usage: head [-n lines] file (...)\n");
		return 1;
	};
	big = 10L;
	nflag = 0;
	success = 0;
	if (strncmp(argv[1], "-n", 2) == 0) {
		if (argc > 3) {
			big = atol(argv[2]);
			if (big < 1) return 0;
			nflag = 2;
		} else goto usage;
	};
	if (argc-nflag-2 > 0) {
		multi = 1;
	} else multi = 0;
	for (i = 1+nflag; i < argc; i++) {
		if (multi) printf("%s:\n", argv[i]);
		if (!(f = fopen(argv[i], "r"))) {
			perror("Cannot open file");
			success = 1;
		} else {
			for (j = 0L; j < big; j++) {
				if (fgets(buf, 8192, f) != NULL)
					printf("%s", buf);
			};
			fclose(f);
		};
		if (multi) if (i < argc-1) printf("\n");
	};
	return success;
}

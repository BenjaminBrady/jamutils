/* tail: output the last few lines (10 by default) of specified files.
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
	long lines, nl, p;
	if (argc < 2) {
usage:
		printf("Usage: tail [-n lines] file (...)\n");
		return 1;
	};
	lines = 10L;
	nflag = 0;
	nl = 0L;
	success = 0;
	if (strncmp(argv[1], "-n", 2) == 0) {
		if (argv[2] != NULL) {
			lines = atol(argv[2]);
			if (lines < 1) return 0;
			nflag = 2;
		} else goto usage;
	};
	if (argc-nflag-2 > 0) {
		multi = 1;
	} else multi = 0;
	for (i = 1+nflag; i < argc; i++) {
		if (multi) printf("%s:\n", argv[i]);
		if (!(f = fopen(argv[i], "r"))) {
			perror("Error opening file");
			success = 2;
		} else {
			fseek(f, 0, SEEK_END);
			for (p = ftell(f); p >= 0; p--) {
				fseek(f, p, SEEK_SET);
				if (fgetc(f) == '\n') {
					nl++;
					if (nl > lines) goto print;
				};
			};
			fseek(f, 0, SEEK_SET);
print:
			while ((fgets(buf, 8192, f)) != NULL)
				printf("%s", buf);
			fclose(f);
			nl = 0L;
		};
		if (multi && i < argc-1) printf("\n");
	};
	return success;
}

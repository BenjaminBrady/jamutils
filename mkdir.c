/* mkdir: make a directory at the specified location.
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
#include <sys/stat.h>
#include <sys/types.h>

#include "jam.h"

void makedir(char *path);

int success = 0;
long p = 0777L;
char *d;

void
makedir(char *path)
{
	char *d = strrchr(path, '/');
	if (d != NULL) {
		*d = 0;
		makedir(path);
		*d = '/';
	};
	if (mkdir(path, p) != 0) {
		printf("An error occured while creating %s\n", path);
		success = 1;
	};
}

int
main(int argc, char *argv[])
{
	int i, mflag;
	if (argc < 2) {
		printf("Usage: mkdir dir (...)\n");
		return 1;
	};
	mflag = 0;
	if (strncmp(argv[1], "-m", 2) == 0) {
		p = atol(argv[2]);
		mflag = 2;
	};
	for (i = 1+mflag; i < argc; i++) {
		makedir(argv[i]);
	};
	return success;
}

/* cleanname: optimise file paths to their most efficient form.
 *
 * This file is part of Jam Coreutils.
 *
 * Copyright (C) 2021-2022 Benjamin Brady <benjamin@benjaminbrady.ie>
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

#include "../arg.h"

char *cleanname(char *file);

char *argv0;

char *
cleanname(char *file)
{
	char *p, *q, *dotdot;
	int isroot = (file[0] == '/');
	p = q = dotdot = file+isroot;
	while (*p) {
		if (p[0] == '/') p++;
		else if (p[0] == '.' && (p[1] == '/' || p[1] == 0)) p += 1;
		else if (p[0] == '.' && p[1] == '.' &&
			(p[2] == '/' || p[2] == 0)) {
			p += 2;
			if (q > dotdot) {
				while (--q > dotdot && *q != '/');
			} else if (!isroot) {
				if (q != file) *q++ = '/';
				*q++ = '.';
				*q++ = '.';
				dotdot = q;
			};
		} else {
			if (q != file+isroot) *q++ = '/';
			while ((*q = *p) != '/' && *q != 0) p++, q++;
		};
	};
	if (q == file) *q++ = '.';
	*q = '\0';
	return file;
}

int
main(int argc, char *argv[])
{
	char *wd = NULL, *ext = NULL;

	ARGBEGIN{
	case 'd':
		if ((wd = ARGF()) != NULL) break;
		/* Fallthrough */
	default:
usage:
		fprintf(stderr, "usage: %s filename...\n", argv0);
		return 1;
	}ARGEND;

	if (argc == 0) goto usage;

	for (; *argv; argv++) {
		if (wd == NULL || *argv[0] == '/') {
			puts(cleanname(*argv));
		} else {
			if (!(ext = malloc(strlen(wd)+1 + strlen(*argv)+1))) {
				perror("malloc");
				return 2;
			};
			sprintf(ext, "%s/%s", wd, *argv);
			puts(cleanname(ext));
			free(ext);
		};
	};

	return 0;
}

/* pwd: print the absolute path to the current working directory.
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
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "arg.h"

char *cleanname(char *file);

char *argv0;
int Lflag = 1;

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
	char *wd, clean_wd[PATH_MAX];
	struct stat dot, pwd;

	ARGBEGIN{
	case 'L': Lflag = 1; break;
	case 'P': Lflag = 0; break;
	default:
		fprintf(stderr, "usage: %s [-L|-P]\n", argv0);
		return 1;
	}ARGEND;

	if (Lflag) {
		if ((wd = getenv("PWD")) == NULL) {
			perror("getenv PWD");
			goto Pflag;
		};
		if ((stat(".", &dot) < 0) || (stat(wd, &pwd) < 0)) {
			perror("stat");
			goto Pflag;
		};
		if ((dot.st_ino == pwd.st_ino) && (dot.st_dev == pwd.st_dev)) {
			strncpy(clean_wd, wd, PATH_MAX);
			if (strncmp(wd, cleanname(clean_wd), PATH_MAX) == 0) {
				puts(clean_wd);
				return 0;
			};
		};

	};

Pflag:
	if ((wd = realpath(".", NULL)) == NULL) {
		perror("realpath");
		return 1;
	};
	puts(wd);
	free(wd);

	return 0;
}

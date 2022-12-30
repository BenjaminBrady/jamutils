/* ls: list the contents of directories.
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
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "arg.h"

void printdir(char *p);

int ret;
int aflg;
char *argv0;

void
printdir(char *p)
{
	int i, n;
	struct dirent **f;

	if ((n = scandir(p, &f, NULL, alphasort)) < 0) {
		fprintf(stderr, "scandir %s: ", p);
		perror(NULL);
		ret = 2;
		return;
	};

	for (i = 0; i < n; i++) {
		if (f[i]->d_type == DT_DIR) {
			if (aflg || ((f[i]->d_name)[0] != '.'))
				printf("%s/\n", f[i]->d_name);
			free(f[i]);
			f[i] = NULL;
		};
	};
	for (i = 0; i < n; i++) {
		if (f[i] == NULL) continue;
		if (aflg || ((f[i]->d_name)[0] != '.'))
			puts(f[i]->d_name);
		free(f[i]);
	};

	free(f);
}

int
main(int argc, char *argv[])
{
	char *in;

	ARGBEGIN{
	case 'a': aflg = 1; break;
	case '-':
		in = ARGF();
		(void)in;
		break;
	default:
		/* TODO: Add POSIX compliance. For now, we just accept and
		 * ignore all flags to force a valid invocation. */
		break;
	}ARGEND;

	if (!argc) {
		printdir(".");
	} else if (argc == 1) {
		printdir(*argv);
	} else for (; *argv; argv++) {
		printf("%s:\n", *argv);
		printdir(*argv);
	};

	return ret;
}

/* rm: remove the specified files.
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
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "arg.h"

#define _(a) (a)

void rm(const char *file);
void rm_contents(const char *dir);
int prompt(void);

char *argv0;
int fflg, iflg, rflg;
int ret;

void
rm(const char *file)
{
	struct stat s;

#ifdef CHECK_ACCESS
	if (access(file, F_OK) < 0) {
		if (!fflg) {
			fprintf(stderr, "access %s: ", file);
			perror(NULL);
			ret = 2;
		};
		return;
	};
#endif
	
	if (lstat(file, &s) < 0) {
		if (!fflg) {
			fprintf(stderr, "lstat %s: ", file);
			perror(NULL);
			ret = 2;
			return;
		};
	};

	if (S_ISDIR(s.st_mode)) {
		if (!rflg) {
			fprintf(stderr, "%s: ", file);
			errno = EISDIR;
			perror(NULL);
			ret = 2;
			return;
		};

		if ((!fflg) && (((access(file, W_OK) < 0) &&
						isatty(STDIN_FILENO)) ||
					(iflg))) {
			fprintf(stderr, _("remove contents of \'%s\'? "),
					file);
			if (!(prompt())) return;
		};

		rm_contents(file);

		if (iflg) {
			fprintf(stderr, _("remove \'%s\'? "), file);
			if (!(prompt())) return;
		};

		if (rmdir(file) < 0) {
			if (!fflg) {
				fprintf(stderr, "rmdir %s: ", file);
				perror(NULL);
				ret = 2;
			};
		};
	} else {
		if ((!fflg) && (((access(file, W_OK) < 0) &&
						isatty(STDIN_FILENO)) ||
					(iflg))) {
			fprintf(stderr, _("remove \'%s\'? "), file);
			if (!(prompt())) return;
		};

		if (unlink(file) < 0) {
			if (!fflg) {
				fprintf(stderr, "unlink %s: ", file);
				perror(NULL);
				ret = 2;
			};
		};
	};
}

void
rm_contents(const char *dir)
{
	int i, n;
	struct dirent **dp;
	char *name, dname[NAME_MAX];
	size_t maxlen;

	if ((n = scandir(dir, &dp, NULL, NULL)) < 0) {
		fprintf(stderr, "scandir %s: ", dir);
		return;
	};

	maxlen = strlen(dir) + 1 + NAME_MAX+1; /* path + / + name */
	if (!(name = (char *) malloc(maxlen))) {
		perror("malloc");
		return;
	};

	for (i = 0; i < n; i++) {
		strncpy(dname, dp[i]->d_name, sizeof(dname));
		free(dp[i]);
		if (strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0)
			continue;
		sprintf(name, "%s/%s", dir, dname);
		rm(name);
	};

	free(dp);
	free(name);
}

int
prompt(void)
{
	/* TODO: add NLS */
	int val, c;

	fflush(stdout);
	c = getchar();
	val = (c == 'y' || c == 'Y');

	while (c != '\n' && c != EOF) c = getchar();

	return val;
}

int
main(int argc, char *argv[])
{
	ARGBEGIN{
	case 'f': iflg = 0; fflg = 1; break;
	case 'i': fflg = 0; iflg = 1; break;
	case 'R': /* equivalent to -r */
	case 'r': rflg = 1; break;
	default:
usage:
		fprintf(stderr, "usage: %s [-fiRr] file...\n", argv0);
		return 1;
	}ARGEND;

	if (argc == 0) {
		if (fflg) {
			return 0;
		} else goto usage;
	};

	for (; *argv; argv++) rm(*argv);

	return ret;
}

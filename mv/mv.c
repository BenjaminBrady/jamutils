/* mv: move files.
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
 * https://www.gnu.org/licenses/>. */
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../arg.h"

#define _(a) (a)

void move(const char *src, const char *target);
int prompt(void);
void move_fs(const char *src, const char *target);

char *argv0;
int fflg, iflg;
int ret;

void
move(const char *src, const char *target)
{
#ifdef CHECK_ACCESS
	if (access(src, F_OK) < 0) {
		if (!fflg) {
			fprintf(stderr, "access %s: ", src);
			perror(NULL);
			ret = 2;
		};
		return;
	};
#endif

	if ((access(target, F_OK) == 0) && (!fflg) && (((access(target, W_OK) <
						0) && isatty(0)) || (iflg))) {
		fprintf(stderr, _("overwrite \'%s\'? "), target);
		if (!(prompt())) return;
	};

	if (rename(src, target) < 0) {
		if (errno == EXDEV) {
#ifndef CHECK_ACCESS
			if (access(src, F_OK) < 0) {
				if (!fflg) {
					fprintf(stderr, "access %s: ", src);
					perror(NULL);
					ret = 2;
				};
				return;
			};
#endif
			move_fs(src, target);
		} else {
			fprintf(stderr, "rename %s, %s: ", src, target);
			perror(NULL);
			ret = 2;
		};
		return;
	};

#ifdef LOG_MOVES
	printf("%s -> %s\n", src, target);
#endif
}

int
prompt(void)
{
	/* TODO: add NLS */
	int val;
	int c = getchar();

	val = (c == 'y' || c == 'Y');
	while (c != '\n' && c != EOF) c = getchar();

	return val;
}

void
move_fs(const char *src, const char *target)
{
	struct stat ss, ts;

	if (access(target, F_OK) == 0) {
		if (lstat(target, &ts) < 0) {
			fprintf(stderr, "lstat %s: ", target);
			perror(NULL);
			ret = 2;
			return;
		};
	} else goto mv;
	if (stat(src, &ss) < 0) {
		fprintf(stderr, "stat %s: ", src);
		perror(NULL);
		ret = 2;
		return;
	};

	if ((ss.st_dev == ts.st_dev) && (ss.st_ino == ts.st_ino)) {
#ifdef LOG_MOVES
		printf("%s -> %s\n", src, target);
#endif
		return;
	};

	if (S_ISDIR(ts.st_mode) && !(S_ISDIR(ss.st_mode))) {
		fprintf(stderr, "%s -> %s: ", src, target);
		errno = EISDIR; /* or use EXDEV */
		perror(NULL);
		ret = 2;
		return;
	};
	if (!(S_ISDIR(ts.st_mode) && S_ISDIR(ss.st_mode))) {
		fprintf(stderr, "%s -> %s: ", src, target);
		errno = ENOTDIR; /* or use EXDEV */
		perror(NULL);
		ret = 2;
		return;
	};

	/* TODO: remove target */

mv:
	/* TODO: copy src to target */
	/* TODO: remove src */

	/* error message for until TODOs are finished */
	fprintf(stderr, "%s -> %s: ", src, target);
	errno = EXDEV;
	perror(NULL);
}

int
main(int argc, char *argv[])
{
	int i;
	size_t len;
	char *target, *base;
	struct stat s;

	ARGBEGIN{
	case 'f': iflg = 0; fflg = 1; break;
	case 'i': fflg = 0; iflg = 1; break;
	default:
usage:
		fprintf(stderr, "usage: %s [-fi] source... target\n", argv0);
		return 1;
	}ARGEND;
	if (argc < 2) goto usage;

	if (argc == 2 && (!((stat(argv[1], &s) == 0) && S_ISDIR(s.st_mode)))) {
		move(argv[0], argv[1]);
	} else {
		len = strlen(argv[argc-1]) + 1 + 1; /* path + / + NUL */
		for (i = 0; i < argc-1; i++) {
			base = basename(argv[i]);
			target = malloc(len+strlen(base)); /* + name */
			sprintf(target, "%s/%s", argv[argc-1], base);
			move(argv[i], target);
			free(target);
		};
	};

	return ret;
}

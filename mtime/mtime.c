/* mtime: print last modification time of each file.
 *
 * This file is part of Jamutils.
 *
 * Copyright (C) 2022 Benjamin Brady <benjamin@benjaminbrady.ie>
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
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "arg.h"

#define atime (1 << 0)
#define mtime (1 << 1)
#define ctime (1 << 2)

const char *tim = "%11lu ";
const char *longtim = "%11lu.%.9ld ";
char *argv0;
int ret;
int lflg;
int format;

int
main(int argc, char *argv[])
{
	struct stat s;

	ARGBEGIN{
	case 'l': lflg = 1; break;
	case 'A': format = (1 << 3) - 1; break;
	case 'a': format |= atime; break;
	case 'm': format |= mtime; break;
	case 'c': format |= ctime; break;
	default:
usage:
		fprintf(stderr, "usage: %s [-aAclm] file...\n", argv0);
		return 1;
	}ARGEND;

	if (!argc) {
		goto usage;
	} else for (; *argv; argv++) {
		if ((stat(*argv, &s)) < 0) {
			fprintf(stderr, "stat %s: ", *argv);
			perror(NULL);
			ret = 2;
		} else {
			if (lflg) {
				if (format & atime) printf(longtim,
						s.st_atim.tv_sec,
						s.st_atim.tv_nsec);

				if (!format || (format & mtime))
					printf(longtim, s.st_mtim.tv_sec,
						s.st_mtim.tv_nsec);

				if (format & ctime) printf(longtim,
						s.st_ctim.tv_sec,
						s.st_ctim.tv_nsec);
			} else {
				if (format & atime) printf(tim,
						s.st_atim.tv_sec);

				if (!format || (format & mtime)) printf(tim,
						s.st_mtim.tv_sec);

				if (format & ctime) printf(tim,
						s.st_ctim.tv_sec);
			};
			puts(*argv);
		};
	};

	return ret;
}

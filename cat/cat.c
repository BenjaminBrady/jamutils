/* cat: concatenate inputted files and write to stdout.
 * 
 * This file is part of Jam Coreutils.
 *
 * Copyright (C) 2022 Benjamin Brady <benjamin@benjaminbrady.ie>
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
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "../arg.h"

void print(int fd, const char *s);
ssize_t writeall(const void *buf, size_t len);

char *argv0;
int ret;

void
print(int fd, const char *s)
{
	char buf[BUFSIZ];
	ssize_t n;

	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		if (writeall(buf, n) < 0) {
			fprintf(stderr, "write %s: ", s);
			perror(NULL);
			return;
		};
	};
}

ssize_t
writeall(const void *buf, size_t len)
{
	ssize_t n;
	const char *p = buf;

	while (len) {
		n = write(1, p, len);
		if (n <= 0) return n;
		p += n;
		len -= n;
	};

	return p - (const char *)buf;
}

int
main(int argc, char *argv[])
{
	int fd;

	ARGBEGIN{
	case 'u': break;
	default:
		fprintf(stderr, "usage: %s [-u] [file ...]\n", argv0);
		return 1;
	}ARGEND;

	if (!argc) {
		print(0, "<stdin>");
	} else for (; *argv; argv++) {
		if (!strcmp(*argv, "-")) {
			print(0, "<stdin>");
		} else {
			if ((fd = open(*argv, O_RDONLY)) < 0) {
				fprintf(stderr, "open %s: ", *argv);
				perror(NULL);
				ret = 2;
			} else {
				print(fd, *argv);
				close(fd);
			};
		};
	};

	return ret;
}

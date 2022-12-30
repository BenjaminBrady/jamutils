/* touch: change file access and modification timestamps.
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
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "arg.h"

#define _(a) (a)

void set_now(void);
void touch(char *file);

char u_msg[] = "usage: %s [-acm] [-r ref_file|-t time|-d date_time] file...\n";
char *argv0;
int ret = 0;
struct timespec now;
struct timespec times[2];
mode_t create_mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;

void
set_now(void)
{
	time_t sec;

	if (clock_gettime(CLOCK_REALTIME, &now) < 0) {
		perror("clock_gettime CLOCK_REALTIME");

		sec = time(NULL);
		if (sec == (time_t)-1) {
			perror("time");
			exit(1);
		} else {
			now.tv_sec = sec;
			now.tv_nsec = 0L;
		};
	};
}

void
touch(char *file)
{
	int fd;

	if ((fd = open(file, O_WRONLY|O_TRUNC)) < 0) {
		if (errno == ENOENT) {
			if ((fd = creat(file, create_mode)) < 0) {
				fprintf(stderr, "creat %s: ", file);
				perror(NULL);
				ret = 2;
				return;
			};
			if (futimens(fd, times) < 0) {
				fprintf(stderr, "futimens %s: ", file);
				perror(NULL);
				ret = 2;
			};
			close(fd);

		} else {
			fprintf(stderr, "open %s: ", file);
			perror(NULL);
			ret = 2;
		};
		return;
	};

	if (utimensat(AT_FDCWD, file, times, 0) < 0) {
		fprintf(stderr, "utimensat %s: ", file);
		perror(NULL);
		ret = 2;
	};

	close(fd);
}

int
main(int argc, char *argv[])
{
	int i;
	char *n;

	/* TODO: finish the program, error for now */
	errno = ENOTSUP;
	fprintf(stderr, "%s: ", argv[0]);
	perror(NULL);
	return 1;

	/* TODO: handle arguments to create timestamps and add -c skip logic */
	set_now();
	/* Sample values for timestamps */
	times[0] = now;
	times[1] = now;

	ARGBEGIN{
	case 'a': case 'c': case 'm': break;
	case 'r':
		if ((n = ARGF())) {};
		break;
	case 't':
		if ((n = ARGF())) {};
		break;
	case 'd':
		if ((n = ARGF())) {};
		break;
	default:
		fprintf(stderr, _(u_msg), argv0);
		return 1;
	}ARGEND;

	for (i = 0; i < argc; i++) {
		touch(argv[i]);
	};

	return 0;
}

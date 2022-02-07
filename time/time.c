/* time: time a simple command.
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
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../arg.h"

char *argv0;

int
main(int argc, char *argv[])
{
	int err, wstatus, ret = 0;
	long cr;
	double rate;
	clock_t t0, t1;
	struct tms tms;
	pid_t pid;

	ARGBEGIN{
	case 'p': break;
	default:
usage:
		fprintf(stderr, "usage: %s [-p] utility [argument...]\n",
				argv0);
		return 1;
	}ARGEND;

	if (!argc) goto usage;

	if ((cr = sysconf(_SC_CLK_TCK)) <= 0) {
		perror("sysconf _SC_CLK_TCK");
		return 2;
	};
	if ((t0 = times(&tms)) == (clock_t)-1) {
		perror("times");
		return 2;
	};

	switch (pid = fork()) {
	case -1:
		perror("fork");
		return 2;
	case 0:
		execvp(argv[0], argv);
		err = errno;
		fprintf(stderr, "execvp %s: ", argv[0]);
		perror(NULL);
		_exit(126 + (err == ENOENT));
	default: break;
	};
	waitpid(pid, &wstatus, 0);

	if ((t1 = times(&tms)) == (clock_t)-1) {
		perror("times");
		return 2;
	};

	if (WIFSIGNALED(wstatus)) {
		fprintf(stderr, "Utility terminated by signal %d\n",
				WTERMSIG(wstatus));
		ret = 128 + WTERMSIG(wstatus);
	};
	if (WIFEXITED(wstatus)) ret = WEXITSTATUS(wstatus);
	rate = 1 / (double)cr;
	fprintf(stderr, "real %f\nuser %f\nsys %f\n",
			(t1 - t0) *      rate,
			tms.tms_cutime * rate,
			tms.tms_cstime * rate);
	return ret;
}

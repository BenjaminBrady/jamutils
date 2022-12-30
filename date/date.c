/* date: print or modify the current time and date.
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
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "arg.h"

#define ssiz 8192

char *argv0;
int uflag;
char s[ssiz];
char *def = "+%a %b %e %H:%M:%S %Z %Y";
char *mdhm     = "%m%d%k%M";
char *mdhmy    = "%m%d%k%M%y";
char *mdhm_s   = "%m%d%k%M.%S";
char *mdhmcy   = "%m%d%k%M%C%y";
char *mdhmy_s  = "%m%d%k%M%y.%S";
char *mdhmcy_s = "%m%d%k%M%C%y.%S";

int
main(int argc, char *argv[])
{
	char *fmt;
	time_t t;
	char *date = NULL;
	struct tm *n;
	struct timespec ts, tp;
	int nsec_obtained = 0;

	ARGBEGIN{
	case 'u': uflag = 1; break;
	default:
usage:
		fprintf(stderr, "usage: %s [-u] [+format]\n"
			"usage: %s [-u] mmddhhmm[[cc]yy]\n", argv0, argv0);
		return 1;
	}ARGEND;
	if (argc == 0) {
		date = def;
	} else date = argv[0];

	if (clock_gettime(CLOCK_REALTIME, &ts) < 0) {
		perror("clock_gettime CLOCK_REALTIME");

		if ((t = time(NULL)) == (time_t)-1) {
			perror("time");
			return 3;
		} else {
			n = uflag ? gmtime(&t) : localtime(&t);
		};
	} else {
		nsec_obtained = 1;
		n = uflag ? gmtime(&ts.tv_sec) : localtime(&ts.tv_sec);
	};

	if (date[0] == '+') {
		strftime(s, ssiz, ++date, n);
		puts(s);
	} else {
		switch (strlen(date)) {
		case 0: case 1: case 2: case 3:
		case 4: case 5: case 6: case 7:
			goto usage;
		case 8:
			fmt = mdhm;
			break;
		case 9:
			goto usage;
		case 10:
			fmt = mdhmy;
			break;
#ifdef DATE_PARSE_SECONDS
		case 11:
			fmt = mdhm_s;
			break;
		case 13:
			fmt = mdhmy_s;
			break;
		case 14:
			goto usage;
		default:
			fmt = mdhmcy_s;
			break;
#else
		case 11:
			goto usage;
		default:
#endif
		case 12:
			fmt = mdhmcy;
			break;
		};
		strptime(date, fmt, n);

		if (nsec_obtained) {
			tp = (struct timespec) {
				.tv_sec = mktime(n),
				.tv_nsec = ts.tv_nsec,
			};
		} else {
			tp = (struct timespec) {
				.tv_sec = mktime(n),
				.tv_nsec = 0L,
			};
		};

		if (clock_settime(CLOCK_REALTIME, &tp) != 0) {
			perror("clock_settime");
			return 2;
		};
	};

	return 0;
}

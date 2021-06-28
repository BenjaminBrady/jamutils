/* date: print the current time and date to stdout.
 * 
 * This file is part of Jam Coreutils.
 *
 * Copyright (C) 2021 Benjamin Brady <benjamin@benjaminbrady.ie>
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
#include <string.h>
#include <time.h>

#include "../arg.h"

#define ssiz 8192

char *argv0;
int uflg;
char *def = "+%a %b %e %H:%M:%S %Z %Y";
char s[ssiz];

int
main(int argc, char *argv[])
{
	time_t t;
	char *date = NULL;
	struct tm *n;
	struct timespec tp;
	ARGBEGIN{
	case 'u':	uflg = 1; break;
	}ARGEND;
	if (argc == 0) {
		date = def;
	} else date = argv[0];
	t = time(NULL);
	n = uflg ? gmtime(&t) : localtime(&t);
	if (date[0] == '+') {
		strftime(s, ssiz, ++date, n);
		printf("%s\n", s);
	} else {
		switch(strlen(date)) {
		case 0: /* FALLTHROUGH */
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			goto invalid;
		case 8:
			strptime(date, "%m%d%k%M", n);
			break;
		case 9:
			goto invalid;
		case 10:
			strptime(date, "%m%d%k%M%y", n);
			break;
		case 11:
			strptime(date, "%m%d%k%M.%S", n);
			break;
		case 12:
			strptime(date, "%m%d%k%M%C%y", n);
			break;
		case 13:
			strptime(date, "%m%d%k%M%y.%S", n);
			break;
		case 14:
invalid:
			printf("Invalid date and time\n");
			return 1;
		default:
			strptime(date, "%m%d%k%M%C%y.%S", n);
		};
		tp.tv_sec = mktime(n);
		tp.tv_nsec = 0L;
		if (clock_settime(CLOCK_REALTIME, &tp) != 0) {
			perror("clock_settime");
			return 1;
		};
	};
	return 0;
}

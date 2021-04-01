/* date: print the current time and date to stdout.
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
#include <stdio.h>
#include <time.h>

#include "jam.h"

#define ifzero(x) if (x < 10) printf("0");
#define delimit ; printf("%s", delim)

inline void hms(struct tm *n);
inline void day(struct tm *n);
inline void wday(struct tm *n);
inline void month(struct tm *n);
inline void year(struct tm *n);

const char *delim = " ";

const char *days[] = {
	"(Sun)", "(Mon)", "(Tue)",
	"(Wed)", "(Thu)", "(Fri)",
	"(Sat)",
};

const char *months[] = {
	"Jan", "Feb", "Mar", "Apr",
	"May", "Jun", "Jul", "Aug",
	"Sep", "Oct", "Nov", "Dec",
};

inline void
hms(struct tm *n)
{
	ifzero(n->tm_hour);
	printf("%d:", n->tm_hour);
	ifzero(n->tm_min);
	printf("%d:", n->tm_min);
	ifzero(n->tm_sec);
	printf("%d", n->tm_sec);
}

inline void
day(struct tm *n)
{
	ifzero(n->tm_mday);
	printf("%d", n->tm_mday);
}

inline void
wday(struct tm *n)
{
	printf("%s", days[n->tm_wday]);
}

inline void
month(struct tm *n)
{
	printf("%s", months[n->tm_mon]);
}

inline void
year(struct tm *n)
{
	printf("%d", n->tm_year + 1900);
}

int
main(void)
{
	time_t t = time(NULL);
	struct tm *n = gmtime(&t);
	day(n) delimit;
	month(n) delimit;
	year(n) delimit;
	wday(n) delimit;
	hms(n);
	printf("\n");
	return 0;
}

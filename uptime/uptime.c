/* uptime: print how long the system has been running.
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
#include <sys/sysinfo.h>

#define ifzero(x) if (x < 10) printf("0")

int
main(void)
{
	unsigned long uptime, d, h, m, s;
	struct sysinfo u;
	sysinfo(&u);
	uptime = u.uptime;
	s = uptime % 60;
	m = ((uptime - s) / 60) % 60;
	h = ((uptime - m - s) / 3600) % 24;
	d = ((uptime - h - m - s) / 86400);
	if (d > 0) printf("%lu days ", d);
	ifzero(h);
	printf("%lu:", h);
	ifzero(m);
	printf("%lu:", m);
	ifzero(s);
	printf("%lu\n", s);
	return 0;
}

/* uname: print system information.
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
 * <https://www.gnu.org/licenses/>. */
#include <stdio.h>
#include <sys/utsname.h>

#include "../arg.h"

#define print_sysname  (1 << 0)
#define print_nodename (1 << 1)
#define print_release  (1 << 2)
#define print_version  (1 << 3)
#define print_machine  (1 << 4)

const char *os = "Jam";
char *argv0;
int flgs, prntd;

int
main(int argc, char *argv[])
{
	struct utsname n;

	uname(&n);

	ARGBEGIN{
	case 'a': flgs = (1 << 6) - 1;    break;
	case 'm': flgs |= print_machine;  break;
	case 'n': flgs |= print_nodename; break;
	case 'r': flgs |= print_release;  break;
	case 'v': flgs |= print_version;  break;
	case 's': flgs |= print_sysname;  break;
	default:
		  fprintf(stderr, "usage: %s [-amnrsv]\n", argv0);
		  return 1;
	}ARGEND;

	if (flgs & print_sysname) {
		fputs(n.sysname, stdout);
		prntd = 1;
	};
	if (flgs & print_nodename) {
		if (prntd) putchar(' ');
		fputs(n.nodename, stdout);
		prntd = 1;
	};
	if (flgs & print_release) {
		if (prntd) putchar(' ');
		fputs(n.release, stdout);
		prntd = 1;
	};
	if (flgs & print_version) {
		if (prntd) putchar(' ');
		fputs(n.version, stdout);
		prntd = 1;
	};
	if (flgs & print_machine) {
		if (prntd) putchar(' ');
		fputs(n.machine, stdout);
		prntd = 1;
	};

	if (flgs == ((1 << 6) - 1)) printf(" %s", os);
	if (!prntd) fputs(n.sysname, stdout);

	putchar('\n');

	return 0;
}

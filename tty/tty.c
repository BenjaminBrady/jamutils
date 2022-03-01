/* tty: return the name of the terminal connected to standard input.
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
#include <stdio.h>
#include <unistd.h>

#include "../arg.h"

#define _(a) (a)

char *argv0;

int
main(int argc, char *argv[])
{
	char *tty;

	ARGBEGIN{
	default:
usage:
		fprintf(stderr, "usage: %s\n", argv0);
		return 2;
	}ARGEND;
	if (argc) goto usage;

	tty = ttyname(STDIN_FILENO);
	puts(tty ? tty : _("not a tty"));

	return !tty;
}

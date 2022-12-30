/* uptime: print the uptime of the system.
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

int
main(void)
{
	int status;
	char time[BUFSIZ]; /* Can be higher than eleven + EOF after 99 days */
	FILE *ps;

	/* There are no POSIX system calls for ascertaining process time;
	 * nonetheless, we are able to use the system's implementation of ps to
	 * check the elapsed time of a process */
	if ((ps = popen("ps -o etime= -p 1", "r")) == NULL) {
		perror("popen");
		return 1;
	};
	(void) fgets(time, sizeof(time), ps);
	status = pclose(ps);

	if (status == 0) fputs(time, stdout);

	return status;
}

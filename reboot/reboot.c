/* reboot: hard reset the system via Linux.
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
#ifdef __linux__
#include <unistd.h>
#include <sys/reboot.h>

int
main(void)
{
	sync();
	return reboot(0x01234567);
}
#else
#include <errno.h>
#include <stdio.h>

int
main(void)
{
	errno = ENOTSUP;
	perror("reboot");
	return 1;
}
#endif

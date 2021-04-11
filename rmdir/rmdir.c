/* rmdir: remove the specified directories.
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
#include <fts.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int
main(int argc, char *argv[])
{
	int i, r;
	FTS *ftsp = NULL;
	FTSENT *curr = NULL;
	char *files[2] = {
		NULL, NULL,
	};
	if (argc < 2) {
		printf("Usage: rmdir dir (...)\n");
		return 1;
	};
	r = 0;
	for (i = 1; i < argc; i++) {
		files[0] = argv[i];
		ftsp = fts_open(files,
				FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, NULL);
		if (ftsp) {
			while ((curr = fts_read(ftsp))) {
				if ((curr->fts_info == FTS_ERR) |
				    (curr->fts_info == FTS_DNR) |
				    (curr->fts_info == FTS_NS)) {
					r = 2;
					perror("fts_read error");
				} else if ((curr->fts_info == FTS_DEFAULT) |
					   (curr->fts_info == FTS_DP)      |
					   (curr->fts_info == FTS_F)       |
					   (curr->fts_info == FTS_SL)      |
					   (curr->fts_info == FTS_SLNONE)) {
					if (remove(curr->fts_accpath) < 0) {
						r = 2;
						perror("remove error");
					};
				};
			};
			curr = NULL;
		} else {
			r = 2;
			perror("fts_open error");
		};
		if (ftsp) fts_close(ftsp);
		ftsp = NULL;
	};
	return r;
}

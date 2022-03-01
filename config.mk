# Jamutils config.mk for use with Makefile.
#
# This file is part of Jamutils.
#
# Copyright (C) 2021-2022 Benjamin Brady <benjamin@benjaminbrady.ie>
#
# Jamutils is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# Jamutils is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# Jamutils; see the file COPYING. If not, see <https://www.gnu.org/licenses/>.

# Jamutils version
VERSION = 1.2.0

# Customise below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# includes and libs
INCS = -I..
LIBS = -lm

# flags
CPPFLAGS = -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700 -D_DEFAULT_SOURCE\
	   -D_BSD_SOURCE -DJAMUTILS_VERSION=\"${VERSION}\"
CFLAGS = -std=c99 -pedantic -Os -Wall -Wextra -Wno-deprecated-declarations\
	 ${INCS} ${CPPFLAGS}
LDFLAGS = ${LIBS}

# compiler
CC = cc

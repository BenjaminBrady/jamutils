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
VERSION = 1.3.0

# Customise below to fit your system

# Paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# Includes and Libraries
INCS = -I.. -I. -I/usr/include
LIBS = -lm -L/usr/lib

# Flags
CPPFLAGS += -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700 -D_DEFAULT_SOURCE\
	    -D_BSD_SOURCE -DJAMUTILS_VERSION=\"${VERSION}\" -D__Jamutils__
#CFLAGS = -g -std=c99 -pedantic -Wall -Wextra -O0 ${INCS} ${CPPFLAGS}
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wno-deprecated-declarations -Os\
	 ${INCS} ${CPPFLAGS}
LDFLAGS += ${LIBS} -s

# Compiler
CC = cc

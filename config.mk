# Jam Coreutils config.mk for use with Makefile

# Jamutils version
VERSION = 1.1.0

# Customise below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# includes and libs
LIBS = -lm

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L\
	   -D_XOPEN_SOURCE=700 -D_GNU_SOURCE -DJAMUTILS_VERSION=\"${VERSION}\"
CFLAGS = -std=c99 -pedantic -Os -Wall -Wextra -Wno-deprecated-declarations\
	 ${CPPFLAGS}
LDFLAGS = ${LIBS}

# compiler
CC = cc

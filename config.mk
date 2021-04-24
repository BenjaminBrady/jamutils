# Jam Coreutils config.mk for use with Makefile
# Customise below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# flags
CFLAGS = -std=c99 -pedantic -Os -Wall -Wextra -Wno-deprecated-declarations -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700 -D_GNU_SOURCE -lm

# compiler
CC = cc

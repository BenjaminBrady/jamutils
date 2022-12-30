# Jamutils
A set of POSIX compliant core utilities written within the C99 standard.

## Abstract
They are a set of strictly conforming XSI userland applications (and therefore
a set of strictly conforming POSIX applications) where defined (e.g. add,
isprime, shutdown, etc. are neither specified in POSIX nor XSI).

Included so far are: add, average, basename, cal, cat, cleanname, cmp, date,
dirname, echo, factor, factorial, head, host, isprime, ls, max, min, mkdir,
mtime, multiply, mv, path, pbd, primes, pwd, random, reboot, return, rm, rmdir,
seq, shutdown, sleep, strings, tail, time, tty, uname, uptime, wc, whoami, and
yes.

## Installation
Edit the config.mk to match your local setup as needed (Jamutils is installed
into the /usr/local namespace by default).

Enter the following command to compile and install Jamutils (run as root if
necessary):

	make clean install

If desired (to return to GNU Coreutils, 9base, etc.), enter the following to
uninstall Jamutils (run as root if necessary):

	make uninstall

The two main configuration options which may be passed as environment variables
are:

	- PREFIX: Prefix of the path where Jamutils is installed.

	- CC: C99 compiler to use. cc by default.

The main targets of the Makefile are:

	- all: Compile Jamutils.

	- clean: Remove all of the generated files (e.g. compiled binaries).

	- dist: Create a .tar.gz distribution of Jamutils.

	- install: Install Jamutils (compiles if necessary).

	- uninstall: Uninstall Jamutils.

Read the Makefile for more information.

## License
Copyright years within Jamutils source files may be listed using range
notation, e.g., 2001-2020, indicating that every year in the range, inclusive,
is a copyrightable year that could otherwise be listed individually.

Copyright (C) 2021-2022 Benjamin Brady <benjamin@benjaminbrady.ie>.

Jamutils (a.k.a. jamutils, Jam Coreutils) is free software: you can
redistribute it and/or modify it under the terms of the GNU General Public
License version 3 or (at your option) any later version. You should have
received a copy of the GNU General Public License along with Jamutils; see the
file COPYING. If not, see <https://www.gnu.org/licenses/>.

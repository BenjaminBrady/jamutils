# jamutils
A set of core utilities written in the C99 standard.

# Abstract
They are highly minimalist by virtue but flags will be added for
functionality purposes as needed in future.

Included so far are: add, average, basename, cal, cat, cleanname, cmp, date,
echo, factor, factorial, head, host, isprime, loop, ls, max, min, mkdir,
multiply, mv, primes, random, reboot, return, rm, seq, shutdown, sleep, tail,
uname, uptime, wc, and whoami.

They each behave as you'd expect from their name. There aren't any manpages
yet; that will be added soon. For now, read the source code if you aren't
sure how something works or what flags it takes (there aren't many flags).
There are one sentence descriptions in the source code header.

# Installation
There aren't any makefiles yet; that too will be added soon. For now you must
compile each program manually. Everything has been tested on gcc, clang,
and tcc. Tested on glibc as far back as version 2.25. The intended flags are:
-std=c99 -pedantic -Wall -Wextra -Os -Wno-deprecated-declarations
-D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700

Of course, use the -lm flag where appropriate.

You can skip the define flags (the ones beginning with D_) since they are
already defined in the main header file.

# License
Copyright (C) 2021 Benjamin Brady under the terms of the GNU General Public
License version 3 or (at your option) any later version. You should have
received a copy of the GNU General Public License along with this program;
see the file COPYING. If not, see <https://www.gnu.org/licenses/>.

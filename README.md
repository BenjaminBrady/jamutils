# Jamutils
A set of core utilities written in the C99 standard.

## Abstract
They are highly minimalist by virtue but flags will be added for
functionality purposes as needed in future.

Included so far are: add, average, basename, cal, cat, cleanname, cmp, date,
echo, factor, factorial, head, host, isprime, loop, ls, max, min, mkdir,
multiply, mv, path, pbd, primes, pwd, random, reboot, return, rm, rmdir, seq,
shutdown, sleep, tail, uname, uptime, wc, and whoami.

## Installation
Edit the config.mk to match your local setup as needed.

Afterwards enter the following command to build and install jamutils (run as
root if necessary):

	make install

If desired (to return to GNU Coreutils, 9base, etc.) you may enter the
following to uninstall jamutils:

	make uninstall

## License
Copyright (C) 2021 Benjamin Brady under the terms of the GNU General Public
License version 3 or (at your option) any later version. You should have
received a copy of the GNU General Public License along with this program;
see the file COPYING. If not, see <https://www.gnu.org/licenses/>.

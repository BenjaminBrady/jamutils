# Jamutils - POSIX core utilities written in C99.
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
.POSIX:

include config.mk

SUBDIRS = add\
	  average\
	  basename\
	  cal\
	  cat\
	  cleanname\
	  cmp\
	  date\
	  dirname\
	  echo\
	  factor\
	  factorial\
	  false\
	  head\
	  host\
	  isprime\
	  ls\
	  max\
	  min\
	  mkdir\
	  mtime\
	  multiply\
	  mv\
	  path\
	  pbd\
	  primes\
	  pwd\
	  random\
	  reboot\
	  return\
	  rm\
	  rmdir\
	  seq\
	  shutdown\
	  sleep\
	  strings\
	  sync\
	  tail\
	  time\
	  touch\
	  true\
	  tty\
	  uname\
	  uptime\
	  wc\
	  whoami\
	  yes

all: options jamutils

options:
	@echo "Jamutils ${VERSION} build options:"
	@echo "CFLAGS  = ${CFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC      = ${CC}"

jamutils:
	@for i in ${SUBDIRS}; do cd $$i; ${CC} -c $$i.c ${CFLAGS} -o $$i.o;\
		${CC} $$i.o ${LDFLAGS} -o $$i; sed\
		"s/JAMUTILS_VERSION/${VERSION}/g" < $$i.1 | gzip > $$i.1.gz;\
		cd ..; done;

clean:
	@for i in ${SUBDIRS}; do cd $$i; rm -f "$$i" "$$i.1.gz" "$$i.o"; cd\
		..; done;
	rm -f jamutils-${VERSION}.tar.gz
	@echo "Cleaned Jamutils"

dist: clean
	mkdir -p jamutils-${VERSION}
	cp COPYING Makefile README.md arg.h config.mk jamutils-${VERSION}
	cp -R ${SUBDIRS} jamutils-${VERSION}
	tar -cf jamutils-${VERSION}.tar jamutils-${VERSION}
	gzip jamutils-${VERSION}.tar
	rm -rf jamutils-${VERSION}
	@echo "Created distribution jamutils-${VERSION}.tar.gz"

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	@for i in ${SUBDIRS}; do cd $$i; cp -f $$i ${DESTDIR}${PREFIX}/bin;\
		cd ..; done;
	@for i in ${SUBDIRS}; do chmod 755 ${DESTDIR}${PREFIX}/bin/$$i; done;
	@echo "Installed Jamutils to ${DESTDIR}${PREFIX}/bin"
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@for i in ${SUBDIRS}; do cd $$i; cp -f $$i.1.gz \
		${DESTDIR}${MANPREFIX}/man1; cd ..; done;
	@for i in ${SUBDIRS}; do chmod 644\
		${DESTDIR}${MANPREFIX}/man1/$$i.1.gz; done;
	@echo "Copied manual pages to ${DESTDIR}${MANPREFIX}/man1"

uninstall:
	@for i in ${SUBDIRS}; do rm -f ${DESTDIR}${PREFIX}/bin/$$i; done;
	@for i in ${SUBDIRS}; do rm -f ${DESTDIR}${MANPREFIX}/man1/$$i.1.gz;\
		done;
	@echo "Uninstalled Jamutils"

.PHONY: all options jamutils clean dist install uninstall

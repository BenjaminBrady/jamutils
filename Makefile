# Jamutils - POSIX core utilities written in C99.
# See COPYING for copyright and license details.
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
	  echo\
	  factor\
	  factorial\
	  head\
	  host\
	  isprime\
	  loop\
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
	  uname\
	  uptime\
	  wc\
	  whoami

all: options jamutils

options:
	@echo Jamutils ${VERSION} build options:
	@echo "CFLAGS  = ${CFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC      = ${CC}"

jamutils:
	@for i in ${SUBDIRS}; do cd $$i; ${CC} $$i.c ${CFLAGS} ${LDFLAGS} -o\
		$$i; cd ..; done;

clean:
	@for i in ${SUBDIRS}; do cd $$i; rm -f $$i; cd ..; done;
	rm -f jamutils-${VERSION}.tar.gz
	@echo cleaned Jamutils

dist: clean
	mkdir -p jamutils-${VERSION}
	cp COPYING Makefile README.md arg.h config.mk jamutils-${VERSION}
	cp -R ${SUBDIRS} jamutils-${VERSION}
	tar -cf jamutils-${VERSION}.tar jamutils-${VERSION}
	gzip jamutils-${VERSION}.tar
	rm -rf jamutils-${VERSION}
	@echo created distribution jamutils-${VERSION}.tar.gz

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	@for i in ${SUBDIRS}; do cd $$i; cp -f $$i ${DESTDIR}${PREFIX}/bin;\
		cd ..; done;
	@for i in ${SUBDIRS}; do chmod 755 ${DESTDIR}${PREFIX}/bin/$$i; done;
	@echo installed Jamutils to ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@for i in ${SUBDIRS}; do cd $$i; cp -f $$i.1\
		${DESTDIR}${MANPREFIX}/man1; cd ..; done;
	@for i in ${SUBDIRS}; do chmod 644 ${DESTDIR}${MANPREFIX}/man1/$$i.1;\
		done;
	@echo Man pages copied to ${DESTDIR}${MANPREFIX}/man1

uninstall:
	@for i in ${SUBDIRS}; do rm -f ${DESTDIR}${PREFIX}/bin/$$i; done;
	@for i in ${SUBDIRS}; do rm -f ${DESTDIR}${MANPREFIX}/man1/$$i.1; done;
	@echo uninstalled Jamutils

.PHONY: all options jamutils clean dist install uninstall

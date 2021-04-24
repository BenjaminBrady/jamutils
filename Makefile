# Jam Coreutils Makefile
# See COPYING for copyright and license details.

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
	  tail\
	  uname\
	  uptime\
	  wc\
	  whoami

all:
	@echo Jamutils build options:
	@echo "CFLAGS	= ${CFLAGS}"
	@echo "CC	= ${CC}"
	@for i in ${SUBDIRS}; do cd $$i; ${CC} $$i.c ${CFLAGS} -o $$i || exit; cd ..; done;

install: all
	# @mkdir ${DESTDIR}${PREFIX}/bin
	# @mkdir ${DESTDIR}${MANPREFIX}/man1
	@for i in ${SUBDIRS}; do cp -f $$i/$$i ${DESTDIR}${PREFIX}/bin; chmod 755 ${DESTDIR}${PREFIX}/bin/$$i; cp -f $$i/$$i.1 ${DESTDIR}${MANPREFIX}/man1/$$i.1; chmod 644 ${DESTDIR}${MANPREFIX}/man1/$$i.1; done;
	@echo installed Jamutils to ${DESTDIR}${PREFIX}/bin
	@echo Man pages copied to ${DESTDIR}${MANPREFIX}/man1

uninstall:
	@for i in ${SUBDIRS}; do rm -f ${DESTDIR}${MANPREFIX}/man1/$$i.1; rm -f ${DESTDIR}${PREFIX}/bin/$$i || exit; cd ..; done;
	@echo uninstalled Jamutils

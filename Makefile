CC?=gcc
CFLAGS?=-D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -Wall -g -std=c99
DESTDIR?=
PREFIX?=${DESTDIR}/usr/local
MANPREFIX?=${PREFIX}/share/man

.PHONY : all clean install uninstall

all : sprompt

sprompt : sprompt.c
	${CC} -o sprompt sprompt.c -lreadline ${CFLAGS}

install : sprompt
	cp sprompt ${PREFIX}/bin/
	cp sprompt.1 ${MANPREFIX}/man1/

uninstall :
	rm -f ${PREFIX}/bin/sprompt
	rm -f ${MANPREFIX}/man1/sprompt.1

clean :
	-rm -f *~ sprompt core *.o

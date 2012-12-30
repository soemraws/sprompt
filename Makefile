include config.mk

.PHONY : all clean install uninstall

all : sprompt

sprompt : sprompt.c
	${CC} -o $@ $< -lreadline ${CFLAGS}

install : sprompt
	cp sprompt ${PREFIX}/bin/
	cp sprompt.1 ${MANPREFIX}/man1/

uninstall :
	rm -f ${PREFIX}/bin/sprompt
	rm -f ${MANPREFIX}/man1/sprompt.1

clean :
	-rm -f *~ sprompt core *.o

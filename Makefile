# rarstatus - minimalist status bar for dwl/dwm
# Logic: Use system-wide CFLAGS for optimization

PREFIX = /usr/local
CC = gcc
# Adding -O2 and -flto as per your system preferences
CFLAGS = -std=c99 -pedantic -Wall  -g -O2
LDFLAGS = -flto

SRC = main.c
OBJ = ${SRC:.c=.o}

all: rarstatus

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h

rarstatus: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f rarstatus ${OBJ}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f rarstatus ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/rarstatus

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/rarstatus

.PHONY: all clean install uninstall

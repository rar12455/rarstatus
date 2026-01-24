# rarstatus - minimalist status bar for dwl/dwm
# Logic: Use system-wide CFLAGS for optimization

PREFIX = /usr/local
CC = gcc

CFLAGS = -std=c99 -pedantic -Wall  -g -O2
LDFLAGS = -flto

SRC = main.c
OBJ = ${SRC:.c=.o}

all: rarstatus

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h util.h components/battery.c

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

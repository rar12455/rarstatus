PREFIX = /usr/local
CC = gcc

CFLAGS  = -std=c99 -Wall -Wextra -pedantic -g -O2
LDFLAGS = -flto

SRC = main.c \
      config.c \
      util.c \
      components/battery.c \
      components/brightness.c \
      components/cat_a_file.c \
      components/datetime.c \
      components/freemem.c \
      components/getkernelversion.c \
      components/getuseddiskinfo.c \
      components/print_human_readable_data.c \
      components/printhostname.c \
      components/run_command.c \
      components/uptime.c \
      components/usedmem.c

OBJ = ${SRC:.c=.o}

all: rarstatus

.c.o:
	${CC} -c ${CFLAGS} $< -o $@

${OBJ}: config.h util.h

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

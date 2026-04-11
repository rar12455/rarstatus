PREFIX = /usr/local
CC = cc

CFLAGS  = -std=c99 -Wall -Wextra -pedantic -g -O2
LDFLAGS = -flto

SRC = main.c \
      config.c \
      util.c \
      components/implementation/battery.c \
      components/implementation/brightness.c \
      components/implementation/cat_a_file.c \
      components/implementation/datetime.c \
      components/implementation/freemem.c \
      components/implementation/getkernelversion.c \
      components/implementation/getuseddiskinfo.c \
      components/implementation/print_human_readable_data.c \
      components/implementation/printhostname.c \
      components/implementation/run_command.c \
      components/implementation/uptime.c \
      components/implementation/usedmem.c \
      components/implementation/cpu_usage.c

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

PREFIX = /usr/local
CC = gcc
LD = ld.lld
# Wildcard automatically picks up all your component implementations
SRC = main.c config.c util.c $(wildcard components/implementation/*.c)
OBJ = ${SRC:.c=.o}

# Base flags required for all builds
BASE_CFLAGS = -std=c99 -Wall -Wextra -pedantic -ffunction-sections -fdata-sections
BASE_LDFLAGS = -Wl,--gc-sections 

# --- Build Modes ---

all: release

release: BASE_CFLAGS += -O3 -flto -march=native -DNDEBUG -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-stack-protector
release: BASE_LDFLAGS += -flto -s
release: clean rarstatus

# Debug: Clang checks for errors, then GCC builds the binary
debug: BASE_CFLAGS += -g -O0 -fno-omit-frame-pointer
debug: clean
	@echo "--- Running Clang Static Analysis ---"
	clang -fsyntax-only ${BASE_CFLAGS} ${CFLAGS} ${SRC}
	@echo "--- Building with GCC ---"
	$(MAKE) rarstatus CC=gcc CFLAGS="${CFLAGS}"

# --- Rules ---

rarstatus: ${OBJ}
	${CC} -o $@ ${OBJ} ${BASE_LDFLAGS}

${OBJ}: config.h util.h

.c.o:
	${CC} -c ${BASE_CFLAGS} ${CFLAGS} $< -o $@

clean:
	rm -f rarstatus ${OBJ}

install: release
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f rarstatus ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/rarstatus

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/rarstatus

.PHONY: all clean debug release install uninstall

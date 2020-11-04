CC = gcc
CFLAGS = -Og -g
LDFLAGS = -lSDL2 -lrnd_game -lrnd_bitmap -lrnd_priorityqueue -lrnd_linkedlist -lchipmunk
SRCS = $(wildcard *.c) $(wildcard objs/*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
OUT = space-etcher
DESTDIR = 
PREFIX = /usr/local/bin

all: gen main

main: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(OUT)

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -f *.o objs/*.o

install: CFLAGS += -O3
install: clean all
	cp -- $(OUT) $(DESTDIR)$(PREFIX)/

docs: FORCE
	doxygen Doxyfile

gen: FORCE
	./objs/gen-include.sh

FORCE: ;

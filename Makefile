CC = gcc
CFLAGS = -Og -g
LDFLAGS = -lSDL2 -lSDL2_gfx -lSDL2_image -lrnd_game -lrnd_bitarray -lrnd_priorityqueue -lrnd_linkedlist -lrnd_hashmap -lchipmunk -lm
SRCS = $(wildcard *.c) $(wildcard obj/*.c)
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
	rm -f *.o obj/*.o

install: CFLAGS += -O3
install: clean all
	cp -- $(OUT) $(DESTDIR)$(PREFIX)/

docs: FORCE
	doxygen Doxyfile

gen: FORCE
	./obj/gen-include.sh

FORCE: ;

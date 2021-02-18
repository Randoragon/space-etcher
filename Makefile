CC = gcc
LINKER = gcc
CFLAGS = -Og -g
LDFLAGS = -lSDL2 -lSDL2_gfx -lSDL2_image \
		  -lrnd_game -lrnd_bitarray -lrnd_priorityqueue -lrnd_linkedlist -lrnd_hashmap -lrnd_utils \
		  -lchipmunk -lm

# All SRCDIR subdirectories that contain source files
DIRS = . objects

SRCDIR = src
OBJDIR = obj
SRCDIRS := $(foreach dir, $(DIRS), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS := $(foreach dir, $(DIRS), $(addprefix $(OBJDIR)/, $(dir)))
SRCS := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
OBJS := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCS:.c=.o))
TARGET = space-etcher
DESTDIR = 
PREFIX = /usr/local/bin

.PHONY: directories all main clean install docs gen profile


all: directories gen main

directories:
	mkdir -p $(SRCDIRS) $(OBJDIRS)

main: $(OBJS)
	$(LINKER) $(LDFLAGS) $(OBJS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS)

profile: CFLAGS += -pg
profile: LDFLAGS += -pg
profile: clean all

install: CFLAGS += -O3
install: LDFLAGS += -O3
install: clean all
	cp -- $(TARGET) $(DESTDIR)$(PREFIX)/

docs:
	doxygen Doxyfile

gen:
	./$(SRCDIR)/objects/generate.sh

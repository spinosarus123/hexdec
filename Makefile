CC         = cc
CSTANDARD  = -std=c11
CWARNINGS  = -Wall -Wextra -Wshadow -pedantic -Wno-unused-result -Wvla
COPTIMIZE  = -O2

CFLAGS     = $(CSTANDARD) $(CWARNINGS) $(COPTIMIZE)
LDFLAGS    = $(CFLAGS)
LDLIBS     =

SRC        = hexdec.c
OBJ        = $(addsuffix .o,$(basename $(SRC)))

PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

all: hexdec

hexdec: $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	cp -f hexdec $(DESTDIR)$(BINDIR)/hexdec
	chmod 755 $(DESTDIR)$(BINDIR)/hexdec

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/hexdec

clean:
	rm *.o

.PHONY: all clean install uninstall

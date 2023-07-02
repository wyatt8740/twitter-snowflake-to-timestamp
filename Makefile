# A simple Makefile for tweet-timestamp
# by Wyatt Ward, 2023

# Tested working in GNU Make, smake (Schily tools, by Joerg Schilling),
# nmake (AT&T AST NMake, by Glenn Fowler), and SunPro Make (Sun Microsystems,
# fork maintained by Joerg Schlling; you may need CC=(your compiler) to be
# set).

STRIP ?= strip
CC ?= cc
CXX ?= c++
CPP ?= cpp
AR ?= ar
LD ?= ld
override CFLAGS += -g

.PHONY: all

all: tweet-timestamp

tweet-timestamp: tweet-timestamp.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f tweet-timestamp

# Strip will die on nonexistant files but will still strip whatever it can
# first
.PHONY: strip

strip:
	$(STRIP) -S tweet-timestamp

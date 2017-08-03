#!/bin/sh

cc=gcc
self_macro=_DEBUG_MODE_EN
source_file=test.c binary_search.c
target=test.exe
libs=
cflags=-g -Wall

all: $(source_file)
	$(cc) -D $(self_macro) $(cflags) $^ -o $(target) $(libs)
clean:
	rm -fr *.o *.txt $(target)

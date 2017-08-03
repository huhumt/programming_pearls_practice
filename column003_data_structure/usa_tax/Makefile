#!/bin/sh

cc=gcc
self_macro=_DEBUG_MODE_EN
source_file=test.c usa_tax.c
target=test.exe
libs=
cflags=

all: $(source_file)
	$(cc) -D $(self_macro) $^ -o $(target) $(cflags) $(libs)
clean:
	rm -fr *.o *.txt $(target)

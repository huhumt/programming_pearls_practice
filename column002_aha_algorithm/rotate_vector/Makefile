#!/bin/sh

cc=gcc
self_macro=-D _DEBUG_MODE_EN
source_file=test.c rotate_vector.c
target=test.exe
libs=
cflags=

all: $(source_file)
	$(cc) $(self_macro) $^ -o $(target) $(cflags) $(libs)
clean:
	rm -fr *.o *.txt $(target)

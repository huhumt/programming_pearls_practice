#!/bin/sh

cc=gcc
self_macro=_DEBUG_MODE_EN
source_file=test.c bitmap_sort.c
target=test.exe

all: $(source_file)
	$(cc) -D $(self_macro) $^ -o $(target)
clean:
	rm -fr *.o *.txt $(target)

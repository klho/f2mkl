CC     ?= gcc
CFLAGS ?= -Wall -O2 -fPIC -shared
MKLINC ?= /usr/include/mkl

.PHONY: clean

libf2mkl.so: f2mkl.c
	$(CC) $(CFLAGS) -I$(MKLINC) $^ -o $@

clean:
	rm -f libf2mkl.so

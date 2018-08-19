CC      ?= gcc
CFLAGS  ?= -Wall -O2 -fPIC -shared
MKLROOT ?= /opt/intel/mkl

.PHONY: clean

libf2mkl.so: f2mkl.c
	$(CC) $(CFLAGS) -I$(MKLROOT)/include $^ -o $@

clean:
	rm -f libf2mkl.so

# Enter your UVAID here
UVAID=10542590
PROGNAME=maze-solver

MKDIR=mkdir
PACK=tar -zcvf
CP=cp -r
RM=rm -rf
CC=gcc
#CFLAGS=-std=c99 -Wall -Wextra -pedantic -g3 -gdwarf-2
CFLAGS=-std=c99 -Wall -Wextra -pedantic -O2

TABLESIZE=932587
#TABLESIZE=684017
#TABLESIZE=1502023

all: spell-checker-glib spell-checker-chaining test-timing 

%.o: %.c
	gcc $(CFLAGS) $< -c -o $@

#glib library
hash-glib.o: hash-glib.c
	gcc $< -c `pkg-config --cflags glib-2.0` $(CFLAGS)

libhash-glib.a: hash-glib.o
	ar rcs libhash-glib.a $<

.PHONY: spell-checker-glib
spell-checker-glib: spell-checker.c libhash-glib.a
	gcc spell-checker.c  -L. -lhash-glib `pkg-config --cflags --libs glib-2.0` $(CFLAGS) -o $@

#glib library
hash-chaining.o: hash-chaining.c
	gcc $< -c $(CFLAGS)

libhash-chaining.a: hash-chaining.o
	ar rcs libhash-chaining.a $<

.PHONY: spell-checker-chaining
spell-checker-chaining: spell-checker.c libhash-chaining.a
	gcc spell-checker.c  -L. -lhash-gchaining $(CFLAGS) -o $@

.PHONY: spell-checker-probing
spell-checker-probing:
	@echo "Make it yourself!"

.PHONY: run
run: all
	@echo "****** glib ******"
	./spell-checker-glib input/british-english-insane.txt input/war-and-peace-ascii.txt $(TABLESIZE)
	@echo "\n****** glib ******"
	./spell-checker-glib input/british-english-insane.txt input/origin-of-species-ascii.txt $(TABLESIZE)

.PHONY: clean
clean:
	rm -f *.o *.a tags spell-checker-glib test-timing

.PHONY: tarball
tarball: $(PROGNAME)
	$(MAKE) remove
	$(MKDIR) $(UVAID)_$(PROGNAME)
	$(CP) * $(UVAID)_$(PROGNAME) || true
	$(PACK) $(UVAID)_$(PROGNAME).tar.gz $(UVAID)_$(PROGNAME)/*
	$(RM) $(UVAID)_$(PROGNAME)

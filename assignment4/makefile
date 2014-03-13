# Enter your UVAID here
UVAID=10542590
PROGNAME=spell-checker

MKDIR=mkdir
PACK=tar -zcvf
CP=cp -r
RM=rm -rf
CC=gcc
CFLAGS=-std=c99 -ggdb -Wall -Wextra -pedantic -O2

TABLESIZE=932587

all: spell-checker-glib spell-checker-probing spell-checker-chaining test-timing

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

#glib library
hash-glib.o: hash-glib.c
	$(CC) $< -c `pkg-config --cflags glib-2.0` $(CFLAGS)

libhash-glib.a: hash-glib.o
	ar rcs libhash-glib.a $<

.PHONY: spell-checker-glib
spell-checker-glib: spell-checker.c libhash-glib.a
	$(CC) spell-checker.c  -L. -lhash-glib `pkg-config --cflags --libs glib-2.0` $(CFLAGS) -o $@

#Chaining library
hash-chaining.o: hash-chaining.c
	$(CC) $< -c $(CFLAGS)

libhash-chaining.a: hash-chaining.o
	ar rcs libhash-chaining.a $<

.PHONY: spell-checker-chaining
spell-checker-chaining: spell-checker.c libhash-chaining.a
	$(CC) spell-checker.c  -L. -lhash-chaining $(CFLAGS) -o $@

#probing library
hash-probing.o: hash-probing.c
	$(CC) $< -c $(CFLAGS)

libhash-probing.a: hash-probing.o
	ar rcs libhash-probing.a $<

.PHONY: spell-checker-probing
spell-checker-probing: spell-checker.c libhash-probing.a
	$(CC) spell-checker.c  -L. -lhash-probing $(CFLAGS) -o $@

.PHONY: run
run: spell-checker-glib spell-checker-probing spell-checker-chaining
	@echo "****** glib ******"
	./spell-checker-glib input/british-english-insane.txt input/war-and-peace-ascii.txt $(TABLESIZE)
	@echo "\n****** glib ******"
	./spell-checker-glib input/british-english-insane.txt input/origin-of-species-ascii.txt $(TABLESIZE)
	@echo
	@echo "\n****** probing ******"
	./spell-checker-probing input/british-english-insane.txt input/war-and-peace-ascii.txt $(TABLESIZE)
	@echo "\n****** probing ******"
	./spell-checker-probing input/british-english-insane.txt input/origin-of-species-ascii.txt $(TABLESIZE)
	@echo
	@echo "\n****** chaining ******"
	./spell-checker-chaining input/british-english-insane.txt input/war-and-peace-ascii.txt $(TABLESIZE)
	@echo "\n****** chaining ******"
	./spell-checker-chaining input/british-english-insane.txt input/origin-of-species-ascii.txt $(TABLESIZE)

.PHONY: clean
clean:
	rm -f *.o *.a tags

.PHONY: remove
remove:
	rm -f *.o *.a *.tar.gz tags spell-checker-* test-timing

.PHONY: tarball
tarball: all
	$(MAKE) remove
	$(MKDIR) $(UVAID)_$(PROGNAME)
	$(CP) * $(UVAID)_$(PROGNAME) || true
	$(PACK) $(UVAID)_$(PROGNAME).tar.gz $(UVAID)_$(PROGNAME)/*
	$(RM) $(UVAID)_$(PROGNAME)

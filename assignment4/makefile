CC=gcc
#CFLAGS=-std=c99 -Wall -Wextra -pedantic -g3 -gdwarf-2
CFLAGS=-std=c99 -Wall -Wextra -pedantic -O2

# TABLESIZE=932587
#TABLESIZE=684017
#TABLESIZE=1502023

all: spell-checker-glib test-timing

%.o: %.c
	gcc $(CFLAGS) $< -c -o $@

hash-glib.o: hash-glib.c
	gcc $< -c `pkg-config --cflags glib-2.0` $(CFLAGS)

libhash-glib.a: hash-glib.o
	ar rcs libhash-glib.a $<

spell-checker-glib: spell-checker.c libhash-glib.a
	gcc spell-checker.c  -L. -lhash-glib `pkg-config --cflags --libs glib-2.0` $(CFLAGS) -o $@

spell-checker-chaining:
	@echo "Make it yourself!"

spell-checker-probing:
	@echo "Make it yourself!"

run: all
	@echo "****** glib ******"
	./spell-checker-glib input/british-english-insane.txt input/war-and-peace-ascii.txt $(TABLESIZE)
	@echo "\n****** glib ******"
	./spell-checker-glib input/british-english-insane.txt input/origin-of-species-ascii.txt $(TABLESIZE)

clean:
	rm -f *.o *.a tags spell-checker-glib test-timing

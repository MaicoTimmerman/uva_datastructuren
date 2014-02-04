# Enter your UVAID here
UVAID=10542590
PROGNAME=pi

KDIR=mkdir
PACK=tar -jcvf
CC=gcc
PREFIXCFLAGS=-Wall -pedantic -std=c99 -lm
SUFFIXCFLAGS=-lm
CP=cp
RM=rm -rf
OFILES=$(subst .c,.o,$(wildcard *.c))

$(PROGNAME): $(OFILES)
	$(CC) $(PREFIXCFLAGS) $(OFILES) -o $(PROGNAME) $(SUFFIXCFLAGS)

%.o: %.c
	$(CC) $(PREFIXCFLAGS) -c $< -o $@

run: $(PROGNAME)
	./$(PROGNAME)

clean:
	$(RM) *.o $(PROGNAME) $(PROGNAME)-$(UVAID).tbz

tarball: $(PROGNAME)
	$(MAKE) clean
	$(MKDIR) $(PROGNAME)-$(UVAID)
	$(CP) * $(PROGNAME)-$(UVAID) || true
	$(PACK) $(PROGNAME)-$(UVAID).tbz $(PROGNAME)-$(UVAID)/*
	$(RM) $(PROGNAME)-$(UVAID)

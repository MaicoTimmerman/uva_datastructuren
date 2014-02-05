# Enter your UVAID here
UVAID=10542590
PROGNAME=pi-approx

MKDIR=mkdir
PACK=tar -zcvf
CC=gcc
PREFIXCFLAGS=-Wall -pedantic -std=c99
SUFFIXCFLAGS=-lm
CP=cp
RM=rm -rf
OFILES=$(subst .c,.o,$(wildcard *.c))

$(PROGNAME): $(OFILES)
	$(CC) $(PREFIXCFLAGS) $(OFILES) -o $(PROGNAME) $(SUFFIXCFLAGS)

%.o: %.c
	$(CC) $(PREFIXCFLAGS) -c $< -o $@

run: $(PROGNAME)
	./$(PROGNAME) 2000000

big: $(PROGNAME)
	./$(PROGNAME) 2000000000

clean:
	$(RM) *.o $(PROGNAME) $(UVAID)_$(PROGNAME).tar.gz

tarball: $(PROGNAME)
	$(MAKE) clean
	$(MKDIR) $(UVAID)_$(PROGNAME)
	$(CP) * $(UVAID)_$(PROGNAME) || true
	$(PACK) $(UVAID)_$(PROGNAME).tar.gz $(UVAID)_$(PROGNAME)/*
	$(RM) $(UVAID)_$(PROGNAME)

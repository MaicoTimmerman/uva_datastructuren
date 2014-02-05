# Enter your UVAID here
UVAID=10542590
PROGNAME=pi-approx

MKDIR=mkdir
PACK=tar -zcvf
CC=gcc
PREFIXCFLAGS=-Wall -pedantic -std=c99
LIBS=
CP=cp
RM=rm -rf
OFILES=$(subst .c,.o,$(wildcard *.c))

$(PROGNAME): $(OFILES)
	$(CC) $(PREFIXCFLAGS) $(OFILES) -o $(PROGNAME) $(LIBS)

%.o: %.c
	$(CC) $(PREFIXCFLAGS) -c $< -o $@

.PHONY: run
run: $(PROGNAME)
	@echo
	./$(PROGNAME) 2000000

.PHONY: runbig
runbig: $(PROGNAME)
	./$(PROGNAME) 2147483647

.PHONY: clean
clean:
	$(RM) *.o $(UVAID)_$(PROGNAME).tar.gz

.PHONY: remove
remove:
	$(RM) *.o $(PROGNAME) $(UVAID)_$(PROGNAME).tar.gz

.PHONY: tarball
tarball: $(PROGNAME)
	$(MAKE) clean
	$(MKDIR) $(UVAID)_$(PROGNAME)
	$(CP) * $(UVAID)_$(PROGNAME) || true
	$(PACK) $(UVAID)_$(PROGNAME).tar.gz $(UVAID)_$(PROGNAME)/*
	$(RM) $(UVAID)_$(PROGNAME)

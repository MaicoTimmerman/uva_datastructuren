# Enter your UVAID here
UVAID=10542590
PROGNAME=shortest-path

MKDIR=mkdir
PACK=tar -zcvf
CC=gcc
PREFIXCFLAGS=-Wall -Wextra -ggdb -pedantic -std=c99
LIBS=
CP=cp -r
RM=rm -rf
OFILES=$(subst .c,.o,$(wildcard *.c))

$(PROGNAME): $(OFILES)
	$(CC) $(PREFIXCFLAGS) $(OFILES) -o $(PROGNAME) $(LIBS)

%.o: %.c
	$(CC) $(PREFIXCFLAGS) -c $< -o ./$@

.PHONY: run
run: $(PROGNAME)
	./$(PROGNAME) map1.txt

.PHONY: tree
tree: $(PROGNAME)
	dot -Tpng tree.dot > tree.png

.PHONY: clean
clean:
	$(RM) *.o tags $(UVAID)_$(PROGNAME).tar.gz

.PHONY: remove
remove:
	$(RM) *.o tags $(PROGNAME) $(UVAID)_$(PROGNAME).tar.gz tree.dot tree.png

.PHONY: tarball
tarball: $(PROGNAME)
	$(MAKE) remove
	$(MKDIR) $(UVAID)_$(PROGNAME)
	$(CP) * $(UVAID)_$(PROGNAME) || true
	$(PACK) $(UVAID)_$(PROGNAME).tar.gz $(UVAID)_$(PROGNAME)/*
	$(RM) $(UVAID)_$(PROGNAME)

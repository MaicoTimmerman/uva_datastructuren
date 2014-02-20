# Enter your UVAID here
UVAID=10542590
PROGNAME=maze-solver

MKDIR=mkdir
PACK=tar -zcvf
CC=gcc
PREFIXCFLAGS=-Wall -ggdb -pedantic -std=c99
LIBS=
CP=cp
RM=rm -rf
OFILES=$(subst .c,.o,$(wildcard *.c))

$(PROGNAME): $(OFILES)
	$(CC) $(PREFIXCFLAGS) $(OFILES) -o $(PROGNAME).out $(LIBS)

%.o: %.c
	$(CC) $(PREFIXCFLAGS) -c $< -o ./$@

.PHONY: run
run: $(PROGNAME)
	@echo "Running the program!"
	./$(PROGNAME).out -m mapDir/map1.txt

.PHONY: runv1
runv1: $(PROGNAME)
	@echo "Running the program!"
	./$(PROGNAME).out -vm mapDir/map1.txt

.PHONY: runv2
runv2: $(PROGNAME)
	@echo "Running the program!"
	./$(PROGNAME).out -vm mapDir/map2.txt

.PHONY: runv3
runv3: $(PROGNAME)
	@echo "Running the program!"
	./$(PROGNAME).out -vm mapDir/map3.txt

.PHONY: clean
clean:
	$(RM) *.o $(UVAID)_$(PROGNAME).tar.gz

.PHONY: remove
remove:
	$(RM) *.o $(PROGNAME).out $(UVAID)_$(PROGNAME).tar.gz

.PHONY: tarball
tarball: $(PROGNAME)
	$(MAKE) remove
	$(MKDIR) $(UVAID)_$(PROGNAME)
	$(CP) * $(UVAID)_$(PROGNAME) || true
	$(PACK) $(UVAID)_$(PROGNAME).tar.gz $(UVAID)_$(PROGNAME)/*
	$(RM) $(UVAID)_$(PROGNAME)

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
	$(CC) $(PREFIXCFLAGS) $(OFILES) -o $(PROGNAME) $(LIBS)

%.o: %.c
	$(CC) $(PREFIXCFLAGS) -c $< -o ./$@

.PHONY: run
run: $(PROGNAME)
	@echo "Running the program!"
	./$(PROGNAME) -m mapDir/map1.txt

.PHONY: runv1
runv1: $(PROGNAME)
	@echo "Running the program!"
	./$(PROGNAME) -vm mapDir/map1.txt

.PHONY: runv2
runv2: $(PROGNAME)
	@echo "Running the program!"
	./$(PROGNAME) -vm mapDir/map2.txt

.PHONY: runv3
runv3: $(PROGNAME)
	@echo "Running the program!"
	./$(PROGNAME) -vm mapDir/map3.txt

.PHONY: runv4
runv4: $(PROGNAME)
	@echo "Running the program!"
	./$(PROGNAME) -vm mapDir/map4.txt

.PHONY: runv5
runv5: $(PROGNAME)
	@echo "Running the program!"
	./$(PROGNAME) -vm mapDir/map5.txt

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

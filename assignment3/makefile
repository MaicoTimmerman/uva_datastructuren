# Enter your UVAID here
UVAID=10542590
PROGNAME=maze-solver

MKDIR=mkdir
PACK=tar -zcvf
CC=gcc
PREFIXCFLAGS=-Wall -ggdb -pedantic -std=c99
LIBS=
CP=cp -r
RM=rm -rf
OFILES=$(subst .c,.o,$(wildcard *.c))

$(PROGNAME): $(OFILES)
	$(CC) $(PREFIXCFLAGS) $(OFILES) -o $(PROGNAME).out $(LIBS)

%.o: %.c
	$(CC) $(PREFIXCFLAGS) -c $< -o ./$@

.PHONY: run
run: $(PROGNAME)
	@echo "\nRun instructions:"
	@echo "make help: Run the program with the -h flag."
	@echo "make run1: Run the algorithm with solver function 1."
	@echo "make run2: Run the algorithm with solver function 2."
	@echo "make runv1: Run the algorithm with solver function 1 -v flag enabled."
	@echo "make runv2: Run the algorithm with solver function 2 -v flag enabled."

.PHONY: run1
run1: $(PROGNAME)
	@echo "\nRunning the program with solver 1!"
	./$(PROGNAME).out -m mapDir/map1.txt -s 1

.PHONY: run2
run2: $(PROGNAME)
	@echo "\nRunning the program with solver 2!"
	./$(PROGNAME).out -m mapDir/map1.txt -s 2

.PHONY: runv1
runv1: $(PROGNAME)
	@echo "\nRunning the program with solver 1 and -v flag!"
	./$(PROGNAME).out -vm mapDir/map1.txt -s 1

.PHONY: runv2
runv2: $(PROGNAME)
	@echo "\nRunning the program with solver 2 and -v flag!"
	./$(PROGNAME).out -vm mapDir/map1.txt -s 2

.PHONY: help
help: $(PROGNAME)
	@echo "\nRunning the program with -h flag!"
	./$(PROGNAME).out -h
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

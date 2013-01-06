# Makefile for WordLadder
#****************************************************************

PROGRAM = WordLadder
OBJECTS = WordLadder.o
DEPENDS = \
   WordLadder.cpp \
   Makefile

ARCH = i386
CPPOPTIONS = -IStanfordCPPLib -arch $(ARCH) -fvisibility-inlines-hidden
LDOPTIONS = -LStanfordCPPLib -arch $(ARCH)
LIB = -lStanfordCPPLib

# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(PROGRAM)

WordLadder: $(OBJECTS)
	g++ -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

WordLadder.o: $(DEPENDS)
	@touch console.h
	g++ -c $(CPPOPTIONS) WordLadder.cpp
	@rm console.h


# ***************************************************************
# Standard entries to remove files from the directories
#    tidy  -- eliminate unwanted files
#    clean -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAM)

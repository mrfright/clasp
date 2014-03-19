CC=cc
LFLAGS=-Wall -ansi -Wpedantic -Wextra -O $(DEBUG)
CFLAGS=-c $(LFLAGS) 
DEBUG=-g
SOURCES=readline.c token.c parse.c tree.c
MAINSOURCES=main.c $(SOURCES)
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(SOURCES:.c=.h)
MAINOBJECTS=$(MAINSOURCES:.c=.o)
EXECUTABLE=clasp
TESTREAD=testread
TESTTOKEN=testtoken
TESTTREE=testtree
TESTS=$(TESTREAD) $(TESTTOKEN) $(TESTTREE)

all: $(MAINSOURCES) $(EXECUTABLE) $(TESTS)

clean:
	rm *.o $(EXECUTABLE) $(TESTS)

#used splint, kind of useless, crashed on /usr/include/ctype.h (don't know why it was looking at that)
#lint: $(SOURCES) $(HEADERS)
#	splint $(SOURCES) $(HEADERS)

$(TESTREAD): $(TESTREAD).o $(OBJECTS)
	$(CC) $(LFLAGS) -o $(TESTREAD) $(TESTREAD).o $(OBJECTS)

$(TESTTOKEN): $(TESTTOKEN).o $(OBJECTS)
	$(CC) $(LFLAGS) -o $(TESTTOKEN) $(TESTTOKEN).o $(OBJECTS)

$(TESTTREE): $(TESTTREE).o $(OBJECTS)
	$(CC) $(LFLAGS) -o $(TESTTREE) $(TESTTREE).o $(OBJECTS)

.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) $<

$(EXECUTABLE): $(MAINOBJECTS)
	$(CC) $(LFLAGS) $(MAINOBJECTS) -o $@

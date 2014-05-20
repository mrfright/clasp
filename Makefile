CC=cc
LFLAGS=-Wall -ansi -Wpedantic -Wextra -O $(DEBUG)
CFLAGS=-c $(LFLAGS) 
DEBUG=-g
SOURCES=readline.c token.c parse.c tree.c env.c eval.c
MAINSOURCES=main.c $(SOURCES)
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(SOURCES:.c=.h)
MAINOBJECTS=$(MAINSOURCES:.c=.o)
EXECUTABLE=clasp
TEST=test

all: $(MAINSOURCES) $(EXECUTABLE) $(TEST)

clean:
	rm *.o $(EXECUTABLE) $(TEST) *.exe *.exe.stackdump

#used splint, kind of useless, crashed on /usr/include/ctype.h (don't know why it was looking at that)
#lint: $(SOURCES) $(HEADERS)
#	splint $(SOURCES) $(HEADERS)

$(TEST): $(TEST).o $(OBJECTS)
	$(CC) $(LFLAGS) -o $(TEST) $(TEST).o $(OBJECTS)

.SUFFIXES: .o .c
.c.o:
	$(CC) $(CFLAGS) $<

$(EXECUTABLE): $(MAINOBJECTS)
	$(CC) $(LFLAGS) $(MAINOBJECTS) -o $@

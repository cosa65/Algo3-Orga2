CC=g++

CFLAGS=-g -Wall -ggdb

LDFLAGS=

INCDIR=

SOURCES=main.cpp aux/mat.h

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=tp

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm tp
	rm main.o
.cpp.o:
	$(CC) -I$(INCDIR) $(CFLAGS) $< -c -o $@

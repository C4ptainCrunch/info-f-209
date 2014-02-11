CC=g++
CFLAGS=-std=c++11 -c
EXECUTABLE=server
SOURCES=Socket.cpp bind.cpp   helpers.cpp  server.cpp thread.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm server
CC=g++
CFLAGS=-std=c++11
SOURCES=server.cpp
OBJECTS=server.cpp helpers.cpp bind.cpp
EXECUTABLE=server
PORT=5001

all: clean $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	rm $(EXECUTABLE) > /dev/null 2>&1 || true

test: $(EXECUTABLE)
	./server $(PORT) & telnet localhost $(PORT)

run: $(EXECUTABLE)
	./server $(PORT)
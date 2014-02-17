CC=g++
CFLAGS=-std=c++11 -c
EXECUTABLE=server
SOURCES=bind.cpp  helpers.cpp  server.cpp thread.cpp UserHandler.cpp ../views/views.cpp ../lib/socket/Socket.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm server
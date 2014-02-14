CC=g++
CFLAGS=-std=c++11 -c
EXECUTABLE=a.out
SOURCES=test.cpp json.cpp utils.cpp
H=test.h json.h utils.h
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:  $(H)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(EXECUTABLE)
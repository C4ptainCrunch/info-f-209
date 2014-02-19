include ../../options.mk

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=$(wildcard *.h)

include ../rules.mk


EXECUTABLE=json

$(EXECUTABLE): $(OBJECTS)
	$(COMPILATOR) $(LDFLAGS) $(OBJECTS) -o $@

clean::
	@rm -f $(EXECUTABLE)
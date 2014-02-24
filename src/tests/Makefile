include ../options.mk

SOURCES=$(wildcard *.cpp) ../lib/json/json.cpp ../lib/json/utils.cpp ../lib/json/ModelUnserializationError.cpp ../lib/json/ParseError.cpp
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=$(wildcard *.h)

EXECUTABLE=json

all : $(SOURCES) $(EXECUTABLE)

test: all
	@for exec in $(EXECUTABLE); do ./$$exec ; done

$(EXECUTABLE): $(OBJECTS)
	$(COMPILATOR) $(LDFLAGS) $^ -o $@

$(EXECUTABLE).o: $(HEADERS)

%.o:%.cpp $(HEADERS)
	$(COMPILATOR) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	@rm -f *.o
	@rm -f $(EXECUTABLE)
	@echo "Cleaning..."
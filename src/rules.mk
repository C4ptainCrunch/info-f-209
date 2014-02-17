all : $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILATOR) $(LDFLAGS) $^ -o $@

$(EXECUTABLE).o: $(HEADERS)

%.o:%.cpp $(HEADERS)
	$(COMPILATOR) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm *.o
	rm $(EXECUTABLE)
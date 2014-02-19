all : $(SOURCES) $(EXECUTABLE)
	@touch build.ok

$(EXECUTABLE): $(OBJECTS)
	$(COMPILATOR) $(LDFLAGS) $^ -o $(BUILD_DIR)/$@

$(EXECUTABLE).o: $(HEADERS)

%.o:%.cpp $(HEADERS)
	$(COMPILATOR) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	@rm -f *.o build.ok
	@rm -f $(EXECUTABLE)
	@echo "Cleaning..."
all : $(OBJECTS)
	@touch build.ok

%.o:%.cpp $(HEADERS)
	$(COMPILATOR) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean::
	@rm -f *.o build.ok
	@echo "Cleaning..."
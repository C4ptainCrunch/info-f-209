all : $(OBJECTS)

%.o:%.cpp $(HEADERS)
	$(COMPILATOR) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean::
	@rm -f *.o
	@echo "Cleaning..."
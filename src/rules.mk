SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(addprefix $(BUILD_DIR)/$(NAME)/,$(subst .cpp,.o,$(SOURCES)))
A=$(BUILD_DIR)/$(NAME).a


.PHONY: all clean

all: $(A)

a:
	@echo $(OBJECTS)

$(BUILD_DIR)/$(NAME)/%.o: %.cpp $(HEADERS) | $(BUILD_DIR)/$(NAME)/
	$(CXX) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(NAME)/:
	@mkdir -p $@

$(A): $(OBJECTS)
	ar -r $@ $(OBJECTS)

clean:
	rm -rf $(BUILD_DIR)/$(NAME)
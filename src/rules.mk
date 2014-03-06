SOURCES=$(filter-out test.cpp,$(wildcard *.cpp))
HEADERS=$(wildcard *.h)
OBJECTS=$(addprefix $(BUILD_DIR)/$(NAME)/,$(subst .cpp,.o,$(SOURCES)))
A=$(BUILD_DIR)/$(NAME).a
DEPSA=$(addsuffix .a,$(addprefix $(BUILD_DIR)/,$(DEPS) $(NAME) libtest))


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
	rm -rf $(BUILD_DIR)/tests/$(NAME)


mtest: $(A) $(DEPSA) test.cpp | $(BUILD_DIR)/tests/
	$(CXX) $(LDFLAGS) $(CFLAGS) $(DEPSA) test.cpp -o $(BUILD_DIR)/tests/$(NAME)

test: mtest
	$(BUILD_DIR)/tests/$(NAME)

$(BUILD_DIR)/tests/:
	mkdir -p $@

$(BUILD_DIR)/%.a:
	make -C $(ROOT) $@
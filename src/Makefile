include options.mk

SUB_PROJETS=client server lib/json lib/socket lib/file views models
EXECUTABLE=client server
BUILD_DIR=$(shell pwd)/build

all: $(BUILD_DIR)
	@echo "Building all..."
	@for dir in $(SUB_PROJETS); do echo "Build $$dir\n============" && $(MAKE) -C $$dir BUILD_DIR=$(BUILD_DIR); done

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

tests: test

test: all
	@echo "\n Building status :"
	@echo "==================="
	@for dir in $(SUB_PROJETS);\
	do\
		tests/buildok.sh $$dir;\
	done


clean:
	@for dir in $(SUB_PROJETS); do $(MAKE) -C $$dir clean > /dev/null; done
	@rm -f build/*
	@echo "Cleaning..."



.PHONY: clean
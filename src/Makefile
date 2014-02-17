include options.mk

SUB_PROJETS=client server lib/json lib/socket lib/file views models
EXECUTABLE=client server

all:
	@echo "Building all..."
	@for dir in $(SUB_PROJETS); do make -C $$dir BUILD_DIR=$(shell pwd)/build; done
	@echo "=============="
	@echo "Done building."

clean:
	@for dir in $(SUB_PROJETS); do make -C $$dir clean > /dev/null; done
	@rm -f build/*
	@echo "Cleaning..."

.PHONY: clean
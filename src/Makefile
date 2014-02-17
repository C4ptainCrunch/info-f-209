include options.mk

SUB_PROJETS=client server lib/json lib/socket lib/file views models
EXECUTABLE=client server
BUILD_DIR=$(shell pwd)/build

all:
	@printf "\e[93mBuilding all...\e[0m\n"
	@for dir in $(SUB_PROJETS); do printf "\n\e[93mBuild $$dir\n============\e[0m\n" && $(MAKE) -C $$dir BUILD_DIR=$(BUILD_DIR); done

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

tests: test

test: clean all
	@printf "\n\e[93m Building status :\e[0m\n"
	@printf "\e[93m===================\e[0m\n"
	@for dir in $(SUB_PROJETS);\
	do\
		tests/buildok.sh $$dir;\
	done


clean:
	@for dir in $(SUB_PROJETS); do $(MAKE) -C $$dir clean > /dev/null; done
	@rm -f build/*
	@printf "\e[93mCleaning...\e[0m\n"



.PHONY: clean

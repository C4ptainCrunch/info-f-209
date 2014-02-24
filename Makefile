include src/options.mk

containing = $(foreach v,$2,$(if $(findstring $1,$v),$v))
not-containing = $(foreach v,$2,$(if $(findstring $1,$v),,$v))

DIRS=src/client/ src/server/ src/lib/*/ src/models/ src/views/

HEADERS=$(wildcard $(addsuffix *.h,$(DIRS)))
SOURCES=$(wildcard $(addsuffix *.cpp,$(DIRS)))

OBJECTS=$(filter-out %/main.o,$(addprefix build/objects/,$(subst .cpp,.o,$(SOURCES))))
SEXECUTABLES=$(addsuffix .cpp,$(basename $(filter %/main.cpp, $(SOURCES))))
EXECUTABLES=$(notdir $(patsubst %/main.cpp,%,$(SEXECUTABLES)))

# include src/latex.mk

all: $(EXECUTABLES)

libs: $(OBJECTS)

$(EXECUTABLES): build/bin/$@

build/bin/$(EXECUTABLES): $(OBJECTS) build/bin
	@echo "Compiling $@"
	@$(CXX) -std=c++11 $(LDFLAGS) $(OBJECTS) $(call containing,$@,$(SEXECUTABLES)) -o build/bin/$@

build/objects/%.o: %.cpp $(dir $@) $(HEADERS)
	@make $(dir $@) > /dev/null
	$(CXX) -std=c++11 $(CFLAGS) -c $< -o $@

build:
	@mkdir build/

build/bin: build
	@mkdir build/bin

build/objects/%/: build
	@mkdir -p $@

.PHONY: clean

clean:
	@echo "Cleaning..."
	@rm -rf build/

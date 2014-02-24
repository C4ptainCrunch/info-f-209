include src/options.mk

DIRS=src/client/ src/server/ src/lib/*/ src/models/ src/views/

HEADERS=$(wildcard $(addsuffix *.h,$(DIRS)))
SOURCES=$(wildcard $(addsuffix *.cpp,$(DIRS)))

OBJECTS=$(filter-out */main.cpp,$(addprefix build/objects/,$(subst .cpp,.o,$(SOURCES))))
EXECUTABLES=$(basename $(filter */main.cpp, $(SOURCES)))

# include src/latex.mk

all: $(OBJECTS)

$(EXECUTABLES): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o build/bin/$@

build/objects/%.o: %.cpp $(dir $@) $(HEADERS)
	@make $(dir $@) > /dev/null
	$(CXX) -std=c++11 $(CFLAGS) -c $< -o $@

build:
	@mkdir build/

build/objects/%/: build
	@mkdir -p $@

.PHONY: clean

clean:
	@echo "Cleaning..."
	@rm -rf build/

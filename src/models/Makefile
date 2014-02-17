ifdef C
    COMPILATOR=$(C)
else
    COMPILATOR=clang++
endif

ifdef N

ifeq ($(COMPILATOR), clang++)
	CFLAGS=-std=c++11 -Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo -g
else
	CFLAGS=-std=c++11 -Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ -Wstrict-null-sentinel -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo -Wzero-as-null-pointer-constant
endif

else
	CFLAGS=-std=c++11
endif

LDFLAGS= -g

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
HEADER=$(wildcard *.hpp)
EXECUTABLE=MatchInstance

all : $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILATOR) $(LDFLAGS) $^ -o $@

$(EXECUTABLE).o: $(HEADER)

%.o:%.cpp
	$(COMPILATOR) $(CFLAGS) -c $< -o $@

run:all
	@echo -e "\e[0;31m================= Run ================\e[0m"
	./$(EXECUTABLE)

.PHONY: clean mrproper

clean:
	rm -f *.o

mrproper: clean
	rm -rf $(EXECUTABLE)

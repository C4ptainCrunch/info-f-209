ifdef C
	CXX=$(C)
else
	ifeq ($(shell uname),Darwin)
		CXX=clang++
	else
		CXX=g++
	endif
endif

ifndef CFLAGS
	CFLAGS=-ggdb
endif

ifndef LDFLAGS
	LDFLAGS=-ggdb
endif

CFLAGS+=-std=c++11

ifdef STRICT
	CFLAGS+=-Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo
	ifneq ($(CXX), clang++)
		CFLAGS+=-Wstrict-null-sentinel -Wnoexcept -Wzero-as-null-pointer-constant
	endif
endif

ifdef DEBUG
	LDFLAGS+= -g
	CFLAGS+= -g
endif

ifndef BUILD_DIR
	BUILD_DIR=.
endif
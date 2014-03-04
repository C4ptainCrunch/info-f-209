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
	CFLAGS=
endif

ifndef LDFLAGS
	LDFLAGS=
endif

CFLAGS+= -std=c++11

ifneq ($(D), 0)
 	CFLAGS+= -ggdb
endif

ifeq ($(S), 1)
	CFLAGS+=-Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo
	ifeq ($(CXX), g++)
		CFLAGS+=-Wstrict-null-sentinel -Wnoexcept -Wzero-as-null-pointer-constant
	endif
endif

ROOT=$(shell git rev-parse --show-toplevel)
BUILD_DIR=$(ROOT)/build
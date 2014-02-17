ifdef C
	COMPILATOR=$(C)
else
	ifeq ($(shell uname),Darwin)
		COMPILATOR=clang++
	else
		COMPILATOR=g++
	endif
endif

ifndef CFLAGS
	CFLAGS=
endif

ifndef LDFLAGS
	LDFLAGS=
endif

CFLAGS+=-std=c++11

ifdef STRICT
	CFLAGS+=-Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo
	ifneq ($(COMPILATOR), clang++)
		CFLAGS+=-Wstrict-null-sentinel -Wnoexcept -Wzero-as-null-pointer-constant
	endif
endif

ifdef DEBUG
	LDFLAGS+= -g
	CFLAGS+= -g
endif
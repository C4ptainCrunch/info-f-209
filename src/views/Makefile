include ../options.mk

INCLUDE=../lib/file/files.cpp ../lib/json/json.cpp ../lib/json/utils.cpp ../lib/socket/Socket.cpp ../models/Manager.cpp ../models/Club.cpp ../models/Team.cpp ../models/Player.cpp ../models/NonFieldPlayer.cpp ../models/Installation.cpp ../models/Item.cpp ../server/UserHandler.cpp ../server/helpers.cpp
SOURCES=$(wildcard *.cpp) $(INCLUDE)
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=$(wildcard *.h) 
EXECUTABLE=views

include ../rules.mk
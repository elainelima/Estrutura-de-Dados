UNAME_S := $(shell uname -s)

# Pra rodar em mac e linux :)

CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib


LIBRARIES	:=
EXECUTABLE	:= pa3.out


all: clean $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	@ [ -d bin ] || mkdir -p bin
	@ [ -d obj ] || mkdir -p obj
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB)  $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

UNAME_S := $(shell uname -s)

# Pra rodar em mac e linux :)

CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib


LIBRARIES	:=
EXECUTABLE	:= pa1.out


all: clean $(BIN)/$(EXECUTABLE)

run: all
	


$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	@ [ -d bin ] || mkdir -p bin
	@ [ -d obj ] || mkdir -p obj
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB)  $^ -o $@ $(LIBRARIES)

clean:
	-rm -rf $(BIN)/*

# ./$(BIN)/$(EXECUTABLE) -a q -z 100000 -s 6 
# 	./$(BIN)/$(EXECUTABLE) -a q3 -z 100000 -s 6
# 	./$(BIN)/$(EXECUTABLE) -a qi -z 19097 -s 25
# 	./$(BIN)/$(EXECUTABLE) -a q3i -z 100000 -s 6


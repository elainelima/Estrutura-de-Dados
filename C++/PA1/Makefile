UNAME_S := $(shell uname -s)

# Pra rodar em mac e linux :)
ifeq ($(UNAME_S),Darwin)
	CXX		  := clang++
	CXX_FLAGS := -Wall -Wextra -std=c++17 -g -Ilib
else
	CXX		  := g++
	CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb
endif

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= main

# ------------------------------------------------------------------------------
# Test config  variables
# ------------------------------------------------------------------------------

# Input path details
INPUT := samples
INPUT_SUFFIX := .ppm
# Output path details
OUTPUT := OUT
OUTPUT_SUFFIX := .pgm
# Preparing test targets names
TEST_TARGETS:= $(basename $(notdir $(wildcard $(INPUT)/*.ppm)))
MEMORY_TARGETS := $(OUTPUT)/ref/$(basename $(notdir $(wildcard $(OUTPUT)/ref/*.out))).log

all: $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE) > file.csv

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	@ [ -d bin ] || mkdir -p bin
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*


# TESTS:

# To use this task create a directory called samples and put into it inputs and
# Expected outputs


# clear test outputs
cleartest: clean
	rm $(OUTPUT)/*

measure: all
	@for SEED in {1..5}; do \
		for VERSION in {1..7}; do \
			./$(BIN)/$(EXECUTABLE) \
			-v $${VERSION} \
			-s $${SEED} \
			-m 50 \
			-k 7 \
			-i $(INPUT)/input.txt \
			-o $(OUTPUT)/out_debug_$${VERSION}_$${SEED}.csv \
			-p $(OUTPUT)/out_debug_$${VERSION}_$${SEED}.out \
			-l \
		;done \
	;done

$(MEMORY_TARGETS):
	./analisamem -i $@.out -p OUT/ref/analisamem

# Memory test:
# Checks the memory access performance using provided test files

.PHONY: mem

# .PHONY: memory  $(OUTPUT)/$(TEST_TARGETS)$(OUTPUT_SUFFIX).log

mem: $(MEMORY_TARGETS)
	echo "$@"
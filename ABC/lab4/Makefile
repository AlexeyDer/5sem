CXX		  := g++
CXX_FLAGS := -Wall -Wextra -g -O3

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
ARGS := 5000
# CASH_MISSES_ARG := perf stat -e cache-misses 

LIBRARIES	:=
EXECUTABLE	:= main

ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

all: $(BIN)/$(EXECUTABLE) 
	$(BIN)/$(EXECUTABLE) $(ARGS) 

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp 
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o  $@ $(LIBRARIES) -lrt

clean:
	-rm $(BIN)/*	
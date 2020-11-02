CXX		  := g++
CXX_FLAGS := -Wall -Wextra -lrt

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
ARGS :=  –m L1 –b 4Mb –l 20

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
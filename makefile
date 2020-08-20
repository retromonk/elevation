CXX       := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include
EXECUTABLE  := main
TEST	:= test

all: $(BIN)/$(EXECUTABLE) 

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/main.cpp $(SRC)/sample/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE)  $^ -o $@

$(BIN)/$(TEST): $(SRC)/test.cpp $(SRC)/sample/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE)  $^ -o $@

test: clean $(BIN)/$(TEST)
	clear
	./$(BIN)/$(TEST)

clean:
	-rm $(BIN)/*
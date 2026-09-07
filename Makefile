# TaskForge — COS 214 Prac 4
# `make`        -> builds the executable ./taskforge
# `make run`    -> builds then runs it
# `make valgrind`-> builds then runs it under valgrind (full leak check)
# `make clean`  -> removes build artefacts

CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Iinclude
TARGET   := taskforge

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)

.PHONY: all run valgrind clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

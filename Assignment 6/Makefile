CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
TARGET := rps

SOURCES := \
	main.cpp \
	Choice.cpp \
	FrequencyStore.cpp \
	RandomStrategy.cpp \
	SmartStrategy.cpp \
	HumanPlayer.cpp \
	ComputerPlayer.cpp \
	GameEngine.cpp \
	ConsoleGameEngine.cpp

OBJECTS := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean

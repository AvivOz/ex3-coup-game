# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDES = -I./include -I./tests

# Source files
SRC_FILES = \
	src/Baron.cpp \
	src/Game.cpp \
	src/General.cpp \
	src/Governor.cpp \
	src/Judge.cpp \
	src/Merchant.cpp \
	src/Player.cpp \
	src/playerFactory.cpp \
	src/Spy.cpp

# GUI files
GUI_FILES = \
	src/GUI/WelcomeScreen.cpp \
	src/GUI/PlayerSelectionScreen.cpp \
	src/GUI/GameScreen.cpp \
	src/GUI/gui.cpp \
	src/GUI/main.cpp

# Test files
TEST_FILES = \
	tests/demo_test.cpp

# Output files
MAIN_OUTPUT = main_app
GUI_OUTPUT = gui_app
TEST_OUTPUT = test_app

# Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all clean gui test valgrind main

# Default target - builds everything
all: $(MAIN_OUTPUT) $(GUI_OUTPUT) $(TEST_OUTPUT)

# Build main application
$(MAIN_OUTPUT): $(SRC_FILES) main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Build GUI application
$(GUI_OUTPUT): $(SRC_FILES) $(GUI_FILES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

# Build test application
$(TEST_OUTPUT): $(SRC_FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Run main demo
main: $(MAIN_OUTPUT)
	./$(MAIN_OUTPUT)

# Run GUI
gui: $(GUI_OUTPUT)
	./$(GUI_OUTPUT)

# Run tests
test: $(TEST_OUTPUT)
	./$(TEST_OUTPUT)

# Run memory leak check
valgrind: $(TEST_OUTPUT)
	valgrind --leak-check=full --track-origins=yes ./$(TEST_OUTPUT)

# Clean build files
clean:
	rm -f $(MAIN_OUTPUT) $(GUI_OUTPUT) $(TEST_OUTPUT)
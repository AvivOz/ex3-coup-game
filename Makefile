CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDES = -Iinclude -IGUI

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

GUI_FILES = \
	GUI/gui.cpp \
	GUI/GameTurnScreen.cpp \
	GUI/main.cpp

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

OUTPUT = gui_app

.PHONY: all clean gui_run

all: $(OUTPUT)

$(OUTPUT): $(SRC_FILES) $(GUI_FILES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

gui_run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)
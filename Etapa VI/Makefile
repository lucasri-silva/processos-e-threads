CXX	    := -g++
CXXFLAGS:= -Wall -std=c++11 -Wextra -fdiagnostics-color=always
BUILD	:= ./bin
OBJ_DIR := $(BUILD)/obj
APP_DIR	:= $(BUILD)
TARGET	:= a.out
INCLUDE	:= -Iinclude/
SRC	    := $(wildcard src/*.cpp)
OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -g -o $@ -c $<
	
$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -g -o $(APP_DIR)/$(TARGET) $(OBJECTS)
	
.PHONY:  all build clean run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	
run:
	./$(BUILD)/$(TARGET)
	
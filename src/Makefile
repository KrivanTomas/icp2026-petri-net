# src/Makefile
# Authors:
# 	Tomáš Křivan

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17


TARGET = main

# Last slash requierd
BUILD_DIR = ../build/


SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Compile object files in build directory
OBJS_PATH = $(patsubst %, $(BUILD_DIR)%, $(OBJS))

TARGET_PATH = $(BUILD_DIR)$(TARGET)


.PHONY: clean build_all

build_all: $(BUILD_DIR) $(TARGET_PATH)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR) 

$(TARGET_PATH): $(OBJS_PATH)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build directory (not the whole directory 
# since it could be same as the source directory)
clean:
	rm -f $(TARGET_PATH) $(BUILD_DIR)*.o

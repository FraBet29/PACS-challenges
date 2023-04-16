CXX = g++
CXXFLAGS = -std=c++20

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

CPPFLAGS = -O3 -Wall -I. -I$(INCLUDE_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TARGET = main

.PHONY = clean distclean

.DEFAULT_GOAL = all

all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)

distclean: clean
	$(RM) main

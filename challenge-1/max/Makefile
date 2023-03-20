CXX = g++
CXXFLAGS = -std=c++20

CPPFLAGS = -O3 -Wall -Iinclude/.

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

.PHONY = clean distclean

.DEFAULT_GOAL = all

all: main 

main: $(OBJS)
	$(CXX) $(OBJS) -o main

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRCS)

clean:
	$(RM) -f $(OBJS)

distclean: clean
	$(RM) -f main

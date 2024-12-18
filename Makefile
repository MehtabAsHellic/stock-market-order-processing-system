CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRCS = main.cpp Order.cpp OrderBook.cpp OrderMatcher.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXEC)
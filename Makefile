CXX = g++
INCLUDES =
SRCS = main.cpp boardHelper.cpp

OBJS = $(SRCS:.cpp=.o)

main: $(OBJS)
	$(CXX) $(OBJS) -o main

%o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o main

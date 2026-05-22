CXX = g++
INCLUDES =
SRCS = main.cpp boardHelper.cpp piece.cpp king.cpp queen.cpp rook.cpp bishop.cpp knight.cpp pawn.cpp

OBJS = $(addprefix build/, $(SRCS:.cpp=.o))

main: build $(OBJS)
	$(CXX) $(OBJS) -o main

build:
	mkdir -p build

build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf build main

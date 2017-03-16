CXX=g++
CXXFLAGS=-g -std=c++0x
OBJ= board.o cell.o main.o

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)

clean:
	rm *.o main

CXX = g++
CXXFLAGS = -Wall -g

main: cube.o main.cpp
	$(CXX) $(CXXFLAGS) cube.o main.cpp -o main

cube.o: cube.cpp cube.h
	$(CXX) $(CXXFLAGS) -c cube.cpp

clean:
	rm main
	rm *.o

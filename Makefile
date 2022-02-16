CXX = g++
CXXFLAGS = -Wall -g

main: engine.o main.cpp
	$(CXX) $(CXXFLAGS) engine.o main.cpp -o main

engine.o: engine.cpp engine.h
	$(CXX) $(CXXFLAGS) -c engine.cpp

clean:
	rm main
	rm *.o

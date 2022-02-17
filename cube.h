#ifndef CUBE_CPP
#define CUBE_CPP

#include <iostream>
using namespace std;

enum Color { WHITE, RED, BLUE, ORANGE, GREEN, YELLOW };

char get_letter(Color color);

class Cube {
	public:
		Cube();
		Cube(const Cube &new_cube);
		void print();
	private:
		Color m_cube[6][9];
};

#endif /* CUBE_CPP */

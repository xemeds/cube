#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <algorithm>

using namespace std;

enum Color { WHITE, RED, BLUE, ORANGE, GREEN, YELLOW };

char get_letter(Color color);

class Cube {
	public:
		Cube();
		Cube(const Cube &new_cube);
		void print();

		void move(string move_code);
		void U();
		void D();
		void L();
		void R();
		void F();
		void B();
	private:
		Color m_cube[6][9];

		void rotate_face(int face);
};

#endif /* CUBE_H */

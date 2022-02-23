// Author: Muhammed Ali Dilek (xemeds)

#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

enum Color { WHITE, RED, BLUE, ORANGE, GREEN, YELLOW };

char get_letter(Color color);
string format(string move_codes);

class Cube {
	public:
		Cube();
		Cube(Color colors[6]);
		Cube(const Cube &new_cube);
		void reset();
		void reset(Color colors[6]);
		void print();

		bool valid_move(string move_code);
		vector<string> get_moves();
		void move(string move_codes);

	private:
		Color m_cube[6][9];
		vector<string> m_moves;

		void rotate_face(int face, bool anticlockwise = false);
		void set_face(int faces[6][2], int pair_amount);
		void X();
		void Y();
		void Z();
		void U();
		void D();
		void L();
		void R();
		void F();
		void B();
		void U_wide();
		void D_wide();
		void L_wide();
		void R_wide();
		void F_wide();
		void B_wide();
		void M();
		void E();
		void S();
};

// Returns the first letter of the color enumeration
char get_letter(Color color) {
	switch (color) {
		case WHITE:
			return 'W';
		case RED:
			return 'R';
		case BLUE:
			return 'B';
		case ORANGE:
			return 'O';
		case GREEN:
			return 'G';
		case YELLOW:
			return 'Y';
		default:
			return 0;
	}
}

// Converts a string of moves to the correct format (uppercasing everything except 'w')
string format(string move_codes) {
	for (long unsigned int i = 0; i < move_codes.size(); i++) {
		if (move_codes[i] == 'W') move_codes[i] = 'w';
		else if (move_codes[i] != 'w') move_codes[i] = toupper(move_codes[i]);
	}
	return move_codes;
}

// Sets the default starting state of the cube
Cube::Cube() {
	Color colors[6] = {WHITE, RED, BLUE, ORANGE, GREEN, YELLOW};
	*this = Cube(colors);
}

// Sets the starting state of the cube with the given face colors
Cube::Cube(Color colors[6]) {
	for (int face = 0; face < 6; face++) {
		for (int tile = 0; tile < 9; tile++) {
			m_cube[face][tile] = colors[face];
		}
	}
}

// Copies the state of the given cube
Cube::Cube(const Cube &cube) {
	for (int face = 0; face < 6; face++) {
		for (int tile = 0; tile < 9; tile++) {
			m_cube[face][tile] = cube.m_cube[face][tile];
		}
	}
}

// Resets the cube to the default starting state
void Cube::reset() {
	*this = Cube();
}

// Resets the cube with the given face colors
void Cube::reset(Color colors[6]) {
	*this = Cube(colors);
}

// Prints the cube using the first letter of the colors
void Cube::print() {
	// Face 0
	for (int row = 0; row < 3; row++) {
		printf("     ");
		for (int tile = 0 + (3 * row); tile < 3 + (3 * row); tile++) {
			printf(" %c", get_letter(m_cube[0][tile]));
		}
		printf("\n");
	}

	// Face 1, 2, 3, 4
	for (int row = 0; row < 3; row++) {
		for (int face = 1; face < 5; face++) {
			for (int tile = 0 + (3 * row); tile < 3 + (3 * row); tile++) {
				printf("%c ", get_letter(m_cube[face][tile]));
			}
		}
		printf("\n");
	}

	// Face 5
	for (int row = 0; row < 3; row++) {
		printf("     ");
		for (int tile = 0 + (3 * row); tile < 3 + (3 * row); tile++) {
			printf(" %c", get_letter(m_cube[5][tile]));
		}
		printf("\n");
	}
}

// Returns true if a given move is valid, false if not
bool Cube::valid_move(string move_code) {
	move_code = format(move_code);

	long unsigned int move_code_size = move_code.size();
	if (move_code_size > 3 || move_code_size == 0) return false;

	if (move_code_size == 3 && (move_code[1] != 'w' || (move_code[2] != '\'' && move_code[2] != '2'))) return false;
	if (move_code_size == 2 && move_code[1] != '\'' && move_code[1] != '2' && move_code[1] != 'w') return false;
	if (move_code[0] != 'X' && move_code[0] != 'Y' && move_code[0] != 'Z' && move_code[0] != 'U' && move_code[0] != 'D' && move_code[0] != 'L' && move_code[0] != 'R' && move_code[0] != 'F' && move_code[0] != 'B' && move_code[0] != 'M' && move_code[0] != 'E' && move_code[0] != 'S') return false;

	return true;
}

// Returns the performed moves on the cube
vector<string> Cube::get_moves() {
	return m_moves;
}

// Performs the given moves on the cube
void Cube::move(string move_codes) {
	move_codes = format(move_codes);

	for (long unsigned int i = 0; i < move_codes.size(); i++) {
		string move_code;
		// Length 3 moves
		if (valid_move(string() + move_codes[i] + move_codes[i + 1] + move_codes[i + 2])) {
			move_code = string() + move_codes[i] + move_codes[i + 1] + move_codes[i + 2];
			i += 2;
		}
		// Length 2 moves
		else if (valid_move(string() + move_codes[i] + move_codes[i + 1])) {
			move_code = string() + move_codes[i] + move_codes[i + 1];
			i++;
		}
		// Length 1 moves
		else if (valid_move(string() + move_codes[i])) {
			move_code = string() + move_codes[i];
		}
		else {
			break;
		}

		m_moves.push_back(move_code);

		if (move_code == "X") X();
		else if (move_code == "Y") Y();
		else if (move_code == "Z") Z();

		else if (move_code == "X'") X(), X(), X();
		else if (move_code == "Y'") Y(), Y(), Y();
		else if (move_code == "Z'") Z(), Z(), Z();

		else if (move_code == "X2") X(), X();
		else if (move_code == "Y2") Y(), Y();
		else if (move_code == "Z2") Z(), Z();

		else if (move_code == "U") U();
		else if (move_code == "D") D();
		else if (move_code == "L") L();
		else if (move_code == "R") R();
		else if (move_code == "F") F();
		else if (move_code == "B") B();

		else if (move_code == "U'") U(), U(), U();
		else if (move_code == "D'") D(), D(), D();
		else if (move_code == "L'") L(), L(), L();
		else if (move_code == "R'") R(), R(), R();
		else if (move_code == "F'") F(), F(), F();
		else if (move_code == "B'") B(), B(), B();

		else if (move_code == "U2") U(), U();
		else if (move_code == "D2") D(), D();
		else if (move_code == "L2") L(), L();
		else if (move_code == "R2") R(), R();
		else if (move_code == "F2") F(), F();
		else if (move_code == "B2") B(), B();

		else if (move_code == "Uw") U_wide();
		else if (move_code == "Dw") D_wide();
		else if (move_code == "Lw") L_wide();
		else if (move_code == "Rw") R_wide();
		else if (move_code == "Fw") F_wide();
		else if (move_code == "Bw") B_wide();

		else if (move_code == "Uw'") U_wide(), U_wide(), U_wide();
		else if (move_code == "Dw'") D_wide(), D_wide(), D_wide();
		else if (move_code == "Lw'") L_wide(), L_wide(), L_wide();
		else if (move_code == "Rw'") R_wide(), R_wide(), R_wide();
		else if (move_code == "Fw'") F_wide(), F_wide(), F_wide();
		else if (move_code == "Bw'") B_wide(), B_wide(), B_wide();

		else if (move_code == "Uw2") U_wide(), U_wide();
		else if (move_code == "Dw2") D_wide(), D_wide();
		else if (move_code == "Lw2") L_wide(), L_wide();
		else if (move_code == "Rw2") R_wide(), R_wide();
		else if (move_code == "Fw2") F_wide(), F_wide();
		else if (move_code == "Bw2") B_wide(), B_wide();

		else if (move_code == "M") M();
		else if (move_code == "E") E();
		else if (move_code == "S") S();

		else if (move_code == "M'") M(), M(), M();
		else if (move_code == "E'") E(), E(), E();
		else if (move_code == "S'") S(), S(), S();

		else if (move_code == "M2") M(), M();
		else if (move_code == "E2") E(), E();
		else if (move_code == "S2") S(), S();
	}
}

// Rotates the tiles of a given face of the cube clockwise or anticlockwise
void Cube::rotate_face(int face, bool anticlockwise /*= false*/) {
	Cube current_cube = *this;

	if (anticlockwise) {
		for (int row = 0; row < 3; row++) {
			for (int tile = 0; tile < 3; tile++) {
				m_cube[face][(3 * row) + tile] = current_cube.m_cube[face][2 - row + (3 * tile)];
			}
		}
	}
	else {
		for (int row = 0; row < 3; row++) {
			for (int tile = 0; tile < 3; tile++) {
				m_cube[face][(3 * row) + tile] = current_cube.m_cube[face][6 + row - (3 * tile)];
			}
		}
	}
}

// Sets the tiles of faces[x][0] to faces[x][1]
void Cube::set_face(int faces[6][2], int pair_amount) {
	Cube current_cube = *this;

	for (int pair = 0; pair < pair_amount; pair++) {
		for (int tile = 0; tile < 9; tile++) m_cube[faces[pair][0]][tile] = current_cube.m_cube[faces[pair][1]][tile];
	}
}

// Rotation move X
void Cube::X() {
	int face_changes[][2] = {{0, 2}, {2, 5}, {4, 0}, {5, 4}};
	set_face(face_changes, 4);

	rotate_face(1, true);
	rotate_face(3);
	rotate_face(4);
	rotate_face(4);
	rotate_face(5);
	rotate_face(5);
}

// Rotation move Y
void Cube::Y() {
	int face_changes[][2] = {{1, 2}, {2, 3}, {3, 4}, {4, 1}};
	set_face(face_changes, 4);

	rotate_face(0);
	rotate_face(5, true);
}

// Rotation move Z
void Cube::Z() {
	int face_changes[][2] = {{0, 1}, {1, 5}, {3, 0}, {5, 3}};
	set_face(face_changes, 4);

	rotate_face(0);
	rotate_face(1);
	rotate_face(2);
	rotate_face(3);
	rotate_face(4, true);
	rotate_face(5);
}

// Up
void Cube::U() {
	Cube current_cube = *this;

	for (int tile = 0; tile < 3; tile++) m_cube[1][tile] = current_cube.m_cube[2][tile];
	for (int tile = 0; tile < 3; tile++) m_cube[2][tile] = current_cube.m_cube[3][tile];
	for (int tile = 0; tile < 3; tile++) m_cube[3][tile] = current_cube.m_cube[4][tile];
	for (int tile = 0; tile < 3; tile++) m_cube[4][tile] = current_cube.m_cube[1][tile];

	rotate_face(0);
}

// Down
void Cube::D() {
	Cube current_cube = *this;

	for (int tile = 6; tile < 9; tile++) m_cube[1][tile] = current_cube.m_cube[4][tile];
	for (int tile = 6; tile < 9; tile++) m_cube[2][tile] = current_cube.m_cube[1][tile];
	for (int tile = 6; tile < 9; tile++) m_cube[3][tile] = current_cube.m_cube[2][tile];
	for (int tile = 6; tile < 9; tile++) m_cube[4][tile] = current_cube.m_cube[3][tile];

	rotate_face(5);
}

// Left
void Cube::L() {
	Cube current_cube = *this;

	for (int row = 0; row < 3; row++) m_cube[0][3 * row] = current_cube.m_cube[4][8 - (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[2][3 * row] = current_cube.m_cube[0][3 * row];
	for (int row = 0; row < 3; row++) m_cube[4][2 + (3 * row)] = current_cube.m_cube[5][6 - (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[5][3 * row] = current_cube.m_cube[2][3 * row];

	rotate_face(1);
}

// Right
void Cube::R() {
	Cube current_cube = *this;

	for (int row = 0; row < 3; row++) m_cube[0][2 + (3 * row)] = current_cube.m_cube[2][2 + (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[2][2 + (3 * row)] = current_cube.m_cube[5][2 + (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[4][3 * row] = current_cube.m_cube[0][8 - (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[5][2 + (3 * row)] = current_cube.m_cube[4][6 - (3 * row)];

	rotate_face(3);
}

// Front
void Cube::F() {
	Cube current_cube = *this;

	for (int row = 0; row < 3; row++) m_cube[0][6 + row] = current_cube.m_cube[1][8 - (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[1][2 + (3 * row)] = current_cube.m_cube[5][row];
	for (int row = 0; row < 3; row++) m_cube[3][3 * row] = current_cube.m_cube[0][6 + row];
	for (int row = 0; row < 3; row++) m_cube[5][row] = current_cube.m_cube[3][6 - (3 * row)];

	rotate_face(2);
}

// Back
void Cube::B() {
	Cube current_cube = *this;

	for (int row = 0; row < 3; row++) m_cube[0][row] = current_cube.m_cube[3][2 + (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[1][3 * row] = current_cube.m_cube[0][2 - row];
	for (int row = 0; row < 3; row++) m_cube[3][2 + (3 * row)] = current_cube.m_cube[5][8 - row];
	for (int row = 0; row < 3; row++) m_cube[5][6 + row] = current_cube.m_cube[1][3 * row];

	rotate_face(4);
}

// Up wide
void Cube::U_wide() { D(), Y(); }

// Down wide
void Cube::D_wide() { U(), Y(), Y(), Y(); }

// Left wide
void Cube::L_wide() { R(), X(), X(), X(); }

// Right wide
void Cube::R_wide() { L(), X(); }

// Front wide
void Cube::F_wide() { B(), Z(); }

// Back wide
void Cube::B_wide() { F(), Z(), Z(), Z(); }

// Slice move M
void Cube::M() {
	Cube current_cube = *this;

	for (int row = 0; row < 3; row++) m_cube[0][1 + (3 * row)] = current_cube.m_cube[4][7 - (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[2][1 + (3 * row)] = current_cube.m_cube[0][1 + (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[4][1 + (3 * row)] = current_cube.m_cube[5][7 - (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[5][1 + (3 * row)] = current_cube.m_cube[2][1 + (3 * row)];
}

// Slice move E
void Cube::E() {
	Cube current_cube = *this;

	for (int row = 0; row < 3; row++) m_cube[1][3 + row] = current_cube.m_cube[4][3 + row];
	for (int row = 0; row < 3; row++) m_cube[2][3 + row] = current_cube.m_cube[1][3 + row];
	for (int row = 0; row < 3; row++) m_cube[3][3 + row] = current_cube.m_cube[2][3 + row];
	for (int row = 0; row < 3; row++) m_cube[4][3 + row] = current_cube.m_cube[3][3 + row];
}

// Slice move S
void Cube::S() {
	Cube current_cube = *this;

	for (int row = 0; row < 3; row++) m_cube[0][3 + row] = current_cube.m_cube[1][7 - (3 * row)];
	for (int row = 0; row < 3; row++) m_cube[1][1 + (3 * row)] = current_cube.m_cube[5][3 + row];
	for (int row = 0; row < 3; row++) m_cube[3][1 + (3 * row)] = current_cube.m_cube[0][3 + row];
	for (int row = 0; row < 3; row++) m_cube[5][3 + row] = current_cube.m_cube[3][7 - (3 * row)];
}

#endif /* CUBE_HPP */

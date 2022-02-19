#include "cube.h"

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

// Sets the starting state of the cube
Cube::Cube() {
	for (int face = 0; face < 6; face++) {
		for (int tile = 0; tile < 9; tile++) {
			switch (face) {
				case 0:
					m_cube[face][tile] = WHITE;
					break;
				case 1:
					m_cube[face][tile] = RED;
					break;
				case 2:
					m_cube[face][tile] = BLUE;
					break;
				case 3:
					m_cube[face][tile] = ORANGE;
					break;
				case 4:
					m_cube[face][tile] = GREEN;
					break;
				case 5:
					m_cube[face][tile] = YELLOW;
					break;
			}
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
	transform(move_code.begin(), move_code.end(), move_code.begin(), ::tolower);

	long unsigned int move_code_size = move_code.size();
	if (move_code_size > 2 || move_code_size == 0) return false;

	if (move_code_size == 2 && move_code[1] != '\'' && move_code[1] != '2') return false;
	if (move_code[0] != 'u' && move_code[0] != 'd' && move_code[0] != 'l' && move_code[0] != 'r' && move_code[0] != 'f' && move_code[0] != 'b') return false;

	return true;
}

// Performs the given moves on the cube
void Cube::move(string move_codes) {
	transform(move_codes.begin(), move_codes.end(), move_codes.begin(), ::tolower);

	for (long unsigned int i = 0; i < move_codes.size(); i++) {
		string move_code;
		// Length 2 moves
		if (valid_move(string() + move_codes[i] + move_codes[i + 1])) {
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

		if (move_code == "u") U();
		else if (move_code == "d") D();
		else if (move_code == "l") L();
		else if (move_code == "r") R();
		else if (move_code == "f") F();
		else if (move_code == "b") B();

		else if (move_code == "u'") U(), U(), U();
		else if (move_code == "d'") D(), D(), D();
		else if (move_code == "l'") L(), L(), L();
		else if (move_code == "r'") R(), R(), R();
		else if (move_code == "f'") F(), F(), F();
		else if (move_code == "b'") B(), B(), B();

		else if (move_code == "u2") U(), U();
		else if (move_code == "d2") D(), D();
		else if (move_code == "l2") L(), L();
		else if (move_code == "r2") R(), R();
		else if (move_code == "f2") F(), F();
		else if (move_code == "b2") B(), B();
	}
}

// Rotates the tiles of a given face of the cube clockwise
void Cube::rotate_face(int face) {
	Cube current_cube = *this;

	for (int row = 0; row < 3; row++) {
		for (int tile = 0; tile < 3; tile++) {
			m_cube[face][(3 * row) + tile] = current_cube.m_cube[face][6 + row - (3 * tile)];
		}
	}
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

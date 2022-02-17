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

// Sets the initial color of the cube
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

// Prints the cube using the first letter of the tile colors
void Cube::print() {
	// Face 0
	printf("     ");
	for (int tile = 0; tile < 3; tile++) printf(" %c", get_letter(m_cube[0][tile]));
	printf("\n     ");
	for (int tile = 3; tile < 6; tile++) printf(" %c", get_letter(m_cube[0][tile]));
	printf("\n     ");
	for (int tile = 6; tile < 9; tile++) printf(" %c", get_letter(m_cube[0][tile]));
	printf("\n");

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
	printf("     ");
	for (int tile = 0; tile < 3; tile++) printf(" %c", get_letter(m_cube[5][tile]));
	printf("\n     ");
	for (int tile = 3; tile < 6; tile++) printf(" %c", get_letter(m_cube[5][tile]));
	printf("\n     ");
	for (int tile = 6; tile < 9; tile++) printf(" %c", get_letter(m_cube[5][tile]));
	printf("\n");
}

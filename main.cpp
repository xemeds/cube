// Author: Muhammed Ali Dilek (xemeds)

#include "cube.h"

int main() {
	Cube cube;

	cube.move("U");
	cube.move("D");
	cube.move("L");
	cube.move("R");
	cube.move("F");
	cube.move("B");

	cube.move("U'");
	cube.move("D'");
	cube.move("L'");
	cube.move("R'");
	cube.move("F'");
	cube.move("B'");

	cube.move("U2");
	cube.move("D2");
	cube.move("L2");
	cube.move("R2");
	cube.move("F2");
	cube.move("B2");

	cube.print();
}

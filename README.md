# Rubik's Cube Library

Single-file Rubik's Cube library. Use it to easily model and perform moves on a Rubik's Cube.

# How to use

## Include

The idea behind single-header file libraries is that they're easy to distribute and deploy because all the code is contained in a single file. By default, the .hpp file here acts as its own header file, i.e. they declare the functions contained in the file but don't actually result in any code getting compiled.

So in addition, you should select exactly one C++ source file that actually instantiates the code, preferably a file you're not editing frequently. This file should define a specific macro to actually enable the function definitions.

	#define CUBE_HPP_IMPLEMENTATION
	#include "cube.hpp"

## Usage

### Creating the cube

The default face colors for the cube are `WHITE, RED, BLUE, ORANGE, GREEN, YELLOW` in order.

Create a cube with:

	Cube cube;

Set a new cube equal to a previous cube with:

	Cube cube2(cube);

or

	Cube cube2 = cube;

Set the face colors to another combination while creating the cube:

	Color colors[6] = {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW};
	Cube cube(colors);

### Resetting the cube

Reset the cube to its default state:

	cube.reset();

Reset the cube to a different face color combination:

	Color colors[6] = {WHITE, ORANGE, GREEN, RED, BLUE, YELLOW};
	cube.reset(colors);

### Printing the cube

Print the cube to the console using the first letter of the colors:

	cube.print();

### Check if a move is valid

To check if a single move is valid:

	bool is_valid = cube.is_valid_move("Bw2");

### Perform a move on the cube

To perform a single move, or a sequence of moves on the cube:

	cube.move("R'");
	cube.move("UL'DBw2");

### Get the performed moves

Get the moves performed on the cube since its reset:

	vector<string> moves = cube.get_moves();

## Valid Moves

All the different moves were added from the [Rubik's Cube Move Notations](https://jperm.net/3x3/moves). Below are all the valid moves (upper or lower casing does not matter).

Basic moves: `U D L R F B U' D' L' R' F' B' U2 D2 L2 R2 F2 B2`
Wide moves: `Uw Dw Lw Rw Fw Bw Uw' Dw' Lw' Rw' Fw' Bw' Uw2 Dw2 Lw2 Rw2 Fw2 Bw2`
Slice moves: `M E S M' E' S' M2 E2 S2`
Rotation moves: `X Y Z X' Y' Z' X2 Y2 Z2`

# How the cube is modelled

The cube is modelled as a 2D array, each subarray being the different face of the cube. These subarrays contain the color of each tile on that face of the cube.

The placement of the faces range from 0 - 5 and can be represented as:

           ___
          /0 /|
         /__/ | 4
        |   |3|
      1 | 2 | /
        |___|/
          5

The placement of the tiles for each face range from 0 to 8 and can be represented as:

     ___ ___ ___
    |   |   |   |
    | 0 | 1 | 2 |
    |___|___|___|
    |   |   |   |
    | 3 | 4 | 5 |
    |___|___|___|
    |   |   |   |
    | 6 | 7 | 8 |
    |___|___|___|

Using this, it is possible to easily access a specific tile of the cube and set its color value:

	cube[face][tile] = WHITE;

Additionally, when printing the cube to the console, the faces are printed in the following order:

	     ___
        |   |
        | 0 |
     ___|___|___ ___
    |   |   |   |   |
    | 1 | 2 | 3 | 4 |
    |___|___|___|___|
        |   |
        | 5 |
        |___|

# References

List of valid moves: [https://jperm.net/3x3/moves](https://jperm.net/3x3/moves)
Single-file library explaination: [https://github.com/nothings/stb](https://github.com/nothings/stb)

# License

This project is under the [MIT](https://github.com/xemeds/cube/blob/main/LICENSE) license.

#include "ChessBoard.h"
// The above also includes <iostream> and <string> but no other

void ChessBoard::copyGrid(const char (&src)[8][8], char (&dst)[8][8]) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            dst[row][col] = src[row][col];
        }
    }
}

// Initializes the ChessBoard
ChessBoard::ChessBoard() {
    copyGrid(originGrid, setupGrid);
	copyGrid(setupGrid, grid);
}

// Overrides << operator to display the board
std::ostream& operator<<(std::ostream& os, const ChessBoard& board) {
    for (int row = 0; row < 8; ++row) {
        os << (8 - row) << " "; // Row labels
        for (int col = 0; col < 8; ++col) {
            os << board.grid[row][col] << ' ';
        }
        os << '\n';
    }
    os << "  a b c d e f g h\n"; // Col labels
    return os;
}

// Gets grid ready for a new game by copying setup grid into it
void ChessBoard::resetBoard() {
	copyGrid(setupGrid, grid);
}

// Clears the entire board - Obviously duh
// We may choose to implement it on grid or setupGrid
void ChessBoard::clearBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            grid[row][col] = '_';
        }
    }
}

// Place a specific piece at a specific coordinate
// This one works on setupGrid
void ChessBoard::setSlot(const std::string& coord, char piece) {
    Coordinate curr = convertCoordinate(coord);
    setupGrid[curr.row][curr.col] = piece;
}

// Reset a coordinate to have nothing
// This one works on setupGrid
void ChessBoard::resetSlot(const std::string& coord) {
	Coordinate curr = convertCoordinate(coord);
	
	setupGrid[curr.row][curr.col] = '_';
}

// Converts a string coordinate, such as a1, b2, c3, ... to two numerical coordinates [x][y]
Coordinate ChessBoard::convertCoordinate(const std::string& input) const {
    // The content is primitive and does not check if input is valid
	int col = input[0] - 'a';
    int row = 8 - (input[1] - '0');
    return {row, col};
}

// Gets the piece sitting at the specified coordinates
char ChessBoard::getSlot(const std::string& input) const {
	Coordinate curr = convertCoordinate(input);
	
	return grid[curr.row][curr.col];
}

// Move a piece from coordinates A to B
void ChessBoard::moveToSlot(const std::string& init, const std::string& dest) {
	if (init == dest) {
        return;
    }

    Coordinate origin = convertCoordinate(init);
    Coordinate destination = convertCoordinate(dest);

    char piece = grid[origin.row][origin.col];
    grid[origin.row][origin.col] = '_';
    grid[destination.row][destination.col] = piece;
}
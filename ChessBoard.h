#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <string>

struct Coordinate {
	int row;
	int col;
};

class ChessBoard {
	char grid[8][8];
	char setupGrid[8][8]; // This may be used to save user custom setup grid
	// The base immutable chess placement
	static constexpr char originGrid[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, // 8 (row 0) - Black pieces
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, // 7 (row 1)
        {'_', '_', '_', '_', '_', '_', '_', '_'}, // 6 (row 2)
        {'_', '_', '_', '_', '_', '_', '_', '_'}, // 5 (row 3)
        {'_', '_', '_', '_', '_', '_', '_', '_'}, // 4 (row 4)
        {'_', '_', '_', '_', '_', '_', '_', '_'}, // 3 (row 5)
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, // 2 (row 6)
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}  // 1 (row 7) - White pieces
		// a   b    c    d    e    f    g    h
    };
	
	// This will convert coordinates from a4, c3, etc to numerical [x][y]
	Coordinate convertCoordinate(const std::string& input) const;
	void copyGrid(const char (&src)[8][8], char (&dst)[8][8]);
	
public:
	ChessBoard();
	// void print(); // Or the << operator overide?
	friend std::ostream& operator<<(std::ostream& os, const ChessBoard& board); // Either this or the above
	void clearBoard();
	void resetBoard();
	void setSlot(const std::string& coord, char piece);
	void resetSlot(const std::string& coord);
	char getSlot(const std::string& input) const; // input can be a4, c3, etc...
	void moveToSlot(const std::string& init, const std::string& dest); // Move a piece from initial coordinates to destination coordinates
};

#endif
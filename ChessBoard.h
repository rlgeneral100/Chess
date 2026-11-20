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
	
	// This will convert coordinates from a4, c3, etc to numerical [x][y]
	Coordinate convertCoordinate(const std::string& input) const;
		
public:
	ChessBoard();
	// void print(); // Or the << operator overide?
	friend std::ostream& operator<<(std::ostream& os, const ChessBoard& board); // Either this or the above
	void clearBoard();
	void setSlot(const std::string& coord, char piece);
	void resetSlot(const std::string& coord);
	char getSlot(const std::string& input) const; // input can be a4, c3, etc...
	void moveToSlot(const std::string& init, const std::string& dest); // Move a piece from initial coordinates to destination coordinates
};

#endif
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <string>

struct Coordinate { // Stores coordinate
	int row;
	int col;
};

class ChessBoard {
	// Board state grids
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

	// Internal coordinate & grid helpers
	// This will convert coordinates from a4, c3, etc to numerical [x][y]
	Coordinate convertCoordinate(const std::string& input) const;
	void copyGrid(const char (&src)[8][8], char (&dst)[8][8]);
	static int my_abs(int x);

	// Piece geometry & validation helpers
	bool KMove(int drow, int dcol) const;
	bool QMove(int drow, int dcol) const;
	bool BMove(int drow, int dcol) const;
	bool NMove(int drow, int dcol) const;
	bool RMove(int drow, int dcol) const;
	bool PMove(int drow, int dcol, bool isWhite, int fromRow, bool take) const;
	bool validMovePiece(int drow, int dcol, char piece, int fromRow, bool take) const;
	bool clearPath(Coordinate init, Coordinate dest, int drow, int dcol, char piece) const;
	bool inCheck(Coordinate init, Coordinate dest, char piece) const;

	// Castling
	bool castleKingSide[2]; // 0 for white, 1 for black (index)
	bool castleQueenSide[2];
	bool castleCheck(Coordinate init, Coordinate dest, char piece) const;
	void rookMovedCaptured(Coordinate pos, char piece);

	// En passant
	bool enPassant[8][8]; // Keeps track of all squares where en passant is possible
	bool enPassantCheck(Coordinate init, Coordinate dest, char piece) const;
	void resetEnPassant();

public:
	// Construction & display
	ChessBoard();
	// void print(); // Or the << operator overide?
	friend std::ostream& operator<<(std::ostream& os, const ChessBoard& board); // Either this or the above

	// Board state & square operations
	void drawSetup() const;
	void clearBoard();
	void resetBoard();
	void resetSetup();
	void setSlot(const std::string& coord, char piece);
	void resetSlot(const std::string& coord);
	char getSlot(const std::string& input) const; // input can be a4, c3, etc...
	void moveToSlot(const std::string& init, const std::string& dest, char promotion = '\0'); // Move a piece from initial coordinates to destination coordinates
	// Added a promotion argument where the default value is null, so normal moves still work

	// Move pipeline entry point
	bool boardSideChecks(const std::string& moveFrom, const std::string& moveTo, char piece) const;
};

#endif
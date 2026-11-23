#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

// Compile lines for Windows
// g++ -std=c++20 -Wall -Wextra ChessBoard.cc GameManager.cc -o chess.exe
// .\chess.exe

// Compile lines for Linux/Unix
// g++ -std=c++20 -Wall -Wextra ChessBoard.cc GameManager.cc -o chess
// .\chess

#include <iostream>
#include <sstream>
#include <string>
#include "ChessBoard.h"

class GameManager {
	ChessBoard board;
	int whiteScore, blackScore;
	// Should those variables be static
	bool gameOn; // Is game on or over
	bool setupOn; // Are we in setup format
	bool whiteTurn; // Is it white or black's turn
	// Some of the following may be public candidates
	/*static?*/ bool validPiece(const std::string& piece) const; // This could be static
	/*static?*/ bool validPos(const std::string& pos) const;
	bool validGame(const std::string& player1, const std::string& player2) const;
	bool validMove(const std::string& moveFrom, const std::string& moveTo);
	int computerLevel(const std::string& colour);
	void printPrompt() const;
	void setupManager(const std::string& s, std::istringstream& input); // Controls altered setup commands
	void gameOnManager(const std::string&s, std::istringstream& input); // Sets up ChessBoard for a new game
	void resignManager(); // Performs necessary resets following a resign
	void invalidInput() const; // Prints statement when input is invalid
	
public: 
	GameManager();
	void runGame(); // Gets the game running
};

#endif
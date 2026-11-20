#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <sstream>
#include <string>

class GameManager {
	ChessBoard board;
	// Should those variables be static
	bool gameOn; // Is game on or over
	bool setupOn; // Are we in setup format
	bool whiteTurn; // Is it white or black's turn
	// Some of the following may be public candidates
	/*static?*/ bool validPiece(const std::string& piece) const; // This could be static
	/*static?*/ bool validPos(const std::string& pos) const;
	void setupManager(const std::string& s, std::istringstream& input); // Controls altered setup commands
	void startGameManager(std::istringstream& input); // Sets up ChessBoard for a new game
	void resignManager(); // Performs necessary resets following a resign
	void invalidInput() const; // Prints statement when input is invalid
	
public: 
	GameManager();
	void runGame(); // Gets the game running
};

#endif
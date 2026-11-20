#include <iostream>
#include <sstream>
#include <string>
#include "ChessBoard.h"

class GameManager {
	ChessBoard board;
	// Should those variables be static
	bool gameOn; // Is game on or over
	bool setupOn; // Are we in setup format
	bool whiteTurn; // Is it white or black's turn
	// Some of the following may be public candidates
	void setupManager(const std::string& gameInput); // Controls altered setup commands
	void startGameManager(std::istringstream& input); // Sets up ChessBoard for a new game
	void resignManager(); // Performs necessary resets following a resign
	void invalidInput() const; // Prints statement when input is invalid
	
public: 
	GameManager();
	void runGame(); // Gets the game
};

GameManager::GameManager() : gameOn(false), setupOn(false), whiteTurn(true) {}

void GameManager::runGame() {
	std::string gameInput;
	while (std::getline(std::cin, gameInput)) {
		if (setupOn) {
			setupManager(gameInput);
			continue; // We skip the rest if on setup mode
		}
		
		std::istringstream input(gameInput); // Converts gameInput into it's own input stream
		std::string s; // This will hold one word at a time
		
		if (!(input >> s)) {
			continue; // If somehow read fails
		}

		if (s == "setup") {
			if (!gameOn) {
				setupOn = true;
			} else {
				std::cout << "Game going\n";
			}
		} else if (s == "game") {
			startGameManager(input);
		} else if (s == "resign") {
			resignManager();
		} else {
			invalidInput(); // This is a function so that it is easier to change the invalid message
		}
	}
}

int main() {
	GameManager game;
	game.runGame();
	return 0;
}
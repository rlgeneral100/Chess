#include <iostream>
#include <sstream>
#include <string>
#include "ChessBoard.h"

class GameManager {
	ChessBoard board;
	bool gameOn; // Is game on or over
	bool whiteTurn; // Is it white or black's turn
	
public:
	GameManager();
	void runGame();
};

GameManager::GameManager() : gameOn(false), whiteTurn(true) {}

void GameManager::runGame() {
	std::string gameInput;
	while (std::getline(std::cin, gameInput)) {
		// We may want to trim whitespaces around gameInput
		if (gameInput == "setup") {
			if (!gameOn) {
				// Setup mode code
			} else {
				std::cout << "Game going\n"; // Setup can only be entered if no game is currently happening
			}
		} else if (gameInput.starts_with("game ")) {
			// This is ugly Java style string management, if anyone has something better, please change it
			size_t firstArgStart = 5; // After "game "
			if (firstArgStart < gameInput.size()) {
				// The following tries to extract playerOne
				size_t firstArgEnd = gameInput.find(' ', firstArgStart);
				std::string playerOne = (firstArgEnd == std::string::npos)
					? gameInput.substr(firstArgStart)
					: gameInput.substr(firstArgStart, firstArgEnd - firstArgStart);
				
				// The following tries to extract player 2
				if (firstArgEnd != std::string::npos && firstArgEnd + 1 < gameInput.size()) {
					size_t secondArgStart = firstArgEnd + 1;
					size_t secondArgEnd = gameInput.find(' ', secondArgStart);
					std::string playerTwo = (secondArgEnd == std::string::npos)
						? gameInput.substr(secondArgStart)
						: gameInput.substr(secondArgStart, secondArgEnd - secondArgStart);
						
					// The following will decide how the game goes based on what players 1 and 2 are, human vs computer
					// To be implemented
				} else {
					std::cout << "Invalid command \n";
				}
			} else {
				std::cout << "Invalid command \n";
			}
		}
	}
}

int main() {
	GameManager game;
	game.runGame();
	return 0;
}
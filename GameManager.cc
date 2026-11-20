#include <sstream>
#include "GameManager.h"
#include "ChessBoard.h"

bool GameManager::validPiece(const std::string& piece) const {
	// Length must be 1, a single character
	if (piece.length() != 1) {
        return false;
    }
	
	// If valid piece, returns true and else returns false
    switch (piece[0]) {
        case 'K': case 'k':
        case 'Q': case 'q':
        case 'B': case 'b':
        case 'N': case 'n':
        case 'R': case 'r':
        case 'P': case 'p':
            return true;
        default:
            return false;
    }
}

bool GameManager::validPos(const std::string& pos) const {
	// Length must be 2, x and y
	if (pos.length() != 2) {
		return false;
	}
	
	// The horizontal position, letters
	switch (pos[0]) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
			break;
		default:
			return false;
	}
	
	// The vertical position, integer 1-8
	if (1 <= pos[1] - '0' && pos[1] - '0' <= 8) {
		return true;
	}
	
	return false;
}

bool GameManager::validGame(std::istringstream& input) {
	std::string player1, player2;
	
	if (!(input >> player1 >> player2)) {
		return false;
	}
	
	if ((player1 == "human" || player1.starts_with("computer")) &&
		(player2 == "human" || player2.starts_with("computer"))) {
		return true;	
	}
	
	return false;
}

/* The issue is that we could either permanently save the setup
until game is turned off or that it only lasts one round. Not
sure which one, I think the former but it would be slightly more work*/
void GameManager::setupManager(const std::string& s, std::istringstream& input) {
	if (s == "+") {
		std::string piece, pos;
		// The following checks if input are valid
		if (!(input >> piece >> pos)) {
            invalidInput();
            return;
        }
		if (!validPiece(piece) || !validPos(pos)) {
			invalidInput();
			return;
		}
		
		// Sets the piece on the board
		board.setSlot(pos, piece[0]);
	} else if (s == "-") {
		std::string pos;
		// The following checks if input are valid
		if (!(input >> pos)) {
            invalidInput();
            return;
        }
		if (!validPos(pos)) {
			invalidInput();
			return;
		}
		
		// Clears slot at pos
		board.resetSlot(pos);
	} else if (s == "=") {
		std::string colour;
		if (!(input >> colour)) {
            invalidInput();
            return;
        }
		
		if (colour == "white") {
			whiteTurn = true;
		} else if (colour == "black") {
			whiteTurn = false;
		} else {
			invalidInput();
		}
	} else if (s == "done") {
		setupOn = false;
	} else {
		invalidInput();
	}
}

void GameManager::gameOnManager(const std::string&s, std::istringstream& input) {
	// To be implemented, complex
}

void GameManager::resignManager() {
	gameOn = false;
	board.resetBoard();
}

void GameManager::invalidInput() const {
	std::cout << "Invalid input\n";
}

GameManager::GameManager() : gameOn(false), setupOn(false), whiteTurn(true) {}

void GameManager::runGame() {
	std::string gameInput;
	while (std::getline(std::cin, gameInput)) {
		std::istringstream input(gameInput); // Converts gameInput into it's own input stream
		std::string s; // This will hold one word at a time
		
		if (!(input >> s)) {
			continue; // If somehow read fails
		}
		
		if (setupOn) {
			setupManager(s, input);
			continue; // We skip the rest if on setup mode
		} else if (gameOn) {
			gameOnManager(s, input);
			continue;
		}

		if (s == "setup") {
			setupOn = true;
		} else if (s == "game") {
			if (validGame(input)) {
				gameOn = true;
				board.resetBoard();
			} else {
				invalidInput();
			}
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
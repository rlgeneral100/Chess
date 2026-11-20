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
	
	if (1 <= pos[1] - '0' && pos[1] - '0' <= 8) {
		return true;
	}
	
	return false;
}

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
		board.setSlot(pos, piece);
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

void GameManager::startGameManager(std::istringstream& input) {
	
}

void GameManager::resignManager() {
	
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
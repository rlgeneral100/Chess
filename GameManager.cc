#include <sstream>
#include "GameManager.h"
#include "ChessBoard.h"

// Checks is the requested piece exists in Chess
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

// Checks if provided position is in correct format
// E.g. a1, a2, ..., b1, b2, ..., h7, h8
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

// Checks if the command "game white black" is in valid format
bool GameManager::validGame(std::istringstream& input) {
	std::string player1, player2;
	
	if (!(input >> player1 >> player2)) {
		return false;
	}
	
	// Players can either be human or computer[1-4]
	if ((player1 == "human" || player1.starts_with("computer")) &&
		(player2 == "human" || player2.starts_with("computer"))) {
		return true;	
	}
	
	return false;
}

// This function will require:
// 1. Moves from and to a valid grid position (within 8x8)
// 2. Moves your piece (white or black depending on turn)
// 3. Moves to empty square or to enemy piece, not yourself
// 4. Does not jump over a piece mid path (Unless knight or castling)
// 5. Does not cause a check
// 6. Pawn required to take diagonally
// 7. Move is respective the piece
bool GameManager::validMove(const std::string& moveFrom, const std::string& moveTo) {
	// 1. Moves from and to a valid grid position (within 8x8)
	if (!validPos(moveFrom) || !validPos(moveTo) || moveFrom == moveTo) {
		return false;
	}

	const char pieceAt = board.getSlot(moveFrom);
	const char pieceTo = board.getSlot(moveTo);

	// 2 & 3. Moves your piece, and moves to empty square or enemy piece (not yourself)
	// TODO: Will require some sort of error printing
	if (whiteTurn) {
		if (pieceAt < 'A' || pieceAt > 'Z') {
			return false;
		} else if (pieceTo != '_' && (pieceTo < 'A' || pieceTo <= 'Z')) {
			// pieceTo is white (friendly)
			return false;
		}
	} else {
		if (pieceAt < 'a' || pieceAt > 'z') {
			return false;
		} else if (pieceTo != '_' && (pieceTo >= 'a' && pieceTo <= 'z')) {
			// pieceTo is black (friendly)
			return false;
		}
	}

	// 4, 5, 6, 7. Piece rules, clear path, pawn diagonal capture, and no self-check
	return board.boardSideChecks(moveFrom, moveTo, pieceAt);
}

/* The issue is that we could either permanently save the setup
until game is turned off or that it only lasts one round. Not
sure which one, I think the former but it would be slightly more work*/
void GameManager::setupManager(const std::string& s, std::istringstream& input) {
	if (s == "+") { // Adds a piece to a square on the grid
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
	} else if (s == "-") { // Clears a square on the grid
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
	} else if (s == "=") { // Assign starting colour
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
	} else if (s == "done") { // Exists setup mode
		setupOn = false;
	} else {
		invalidInput();
	}
}

// Main function in charge of an ongoing game
void GameManager::gameOnManager(const std::string& s, std::istringstream& input) {
	// To be implemented, complex
	if (s == "resign") {
		resignManager();
		return;
	} else if (s == "move") {
		std::string moveFrom, moveTo;
		
		if (!(input >> moveFrom >> moveTo)) {
			invalidInput();
			return;
		}
		
		board.moveToSlot(moveFrom, moveTo); // Valid move checks and pawn taking checks to be implemented
	} else {
		invalidInput();
	}
}

// For resigning a game
// Currently missing score and who lost implementation
void GameManager::resignManager() {
	gameOn = false;
	board.resetBoard();
}

// This function is responsible for printing when there are invalid inputs
// It is a function so we can uniformly change all prints in one place
void GameManager::invalidInput() const {
	std::cout << "Invalid input\n";
}

// Constructor
GameManager::GameManager() : gameOn(false), setupOn(false), whiteTurn(true) {}

// Loops as long as game is running
void GameManager::runGame() {
	std::string gameInput;
	while (std::getline(std::cin, gameInput)) {
		// istringstream was used so we can easily use >> operator
		// to extract all sections of a command
		// It lets us treat the string as if it was still read from stream
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
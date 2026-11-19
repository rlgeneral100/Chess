#include <iostream>
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

int main() {
	return 0;
}
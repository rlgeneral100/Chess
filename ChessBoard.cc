#include "ChessBoard.h"
// The above also includes <iostream> and <string> but no other

// Copies one grid into another - passes by reference
void ChessBoard::copyGrid(const char (&src)[8][8], char (&dst)[8][8]) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            dst[row][col] = src[row][col];
        }
    }
}

// Initializes the ChessBoard
// Constructor
ChessBoard::ChessBoard() {
    copyGrid(originGrid, setupGrid);
	copyGrid(setupGrid, grid);
}

// Overrides << operator to display the board
std::ostream& operator<<(std::ostream& os, const ChessBoard& board) {
    for (int row = 0; row < 8; ++row) {
        os << (8 - row) << " "; // Row labels
        for (int col = 0; col < 8; ++col) {
            os << board.grid[row][col] << ' ';
        }
        os << '\n';
    }
    os << "  a b c d e f g h\n"; // Col labels
    return os;
}

// Gets grid ready for a new game by copying setup grid into it
void ChessBoard::resetBoard() {
	copyGrid(setupGrid, grid);
}

// Clears the entire board - Obviously duh
// We may choose to implement it on grid or setupGrid
void ChessBoard::clearBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            grid[row][col] = '_';
        }
    }
}

// Place a specific piece at a specific coordinate
// This one works on setupGrid
void ChessBoard::setSlot(const std::string& coord, char piece) {
    Coordinate curr = convertCoordinate(coord);
    setupGrid[curr.row][curr.col] = piece;
}

// Reset a coordinate to have nothing
// This one works on setupGrid
void ChessBoard::resetSlot(const std::string& coord) {
	Coordinate curr = convertCoordinate(coord);
	
	setupGrid[curr.row][curr.col] = '_';
}

// Converts a string coordinate, such as a1, b2, c3, ... to two numerical coordinates [x][y]
Coordinate ChessBoard::convertCoordinate(const std::string& input) const {
    // The content is primitive and does not check if input is valid
	int col = input[0] - 'a';
    int row = 8 - (input[1] - '0');
    return {row, col};
}

// Gets the piece sitting at the specified coordinates
char ChessBoard::getSlot(const std::string& input) const {
	Coordinate curr = convertCoordinate(input);
	
	return grid[curr.row][curr.col];
}

// Move a piece from coordinates A to B
void ChessBoard::moveToSlot(const std::string& init, const std::string& dest) {
	if (init == dest) {
        return;
    }

    Coordinate origin = convertCoordinate(init);
    Coordinate destination = convertCoordinate(dest);

    char piece = grid[origin.row][origin.col];
    grid[origin.row][origin.col] = '_';
    grid[destination.row][destination.col] = piece;
}

// Idk if we can use <cmath> so just implemented my own abs
int ChessBoard::my_abs(int x) {
	return (x < 0) ? -x : x;
}

// The following checks if the move is valid for each piece
// drow means delta row, the change in row movement (may be passed as abs)
// dcol is delta column, the change in col movement (may be passed as abs)

// Change is at most 1 for row and col and not both 0
bool ChessBoard::KMove(int drow, int dcol) {
	return drow <= 1 && dcol <= 1 && !(drow == 0 && dcol == 0);
}

// Change must be the same along row and col and non-zero
bool ChessBoard::BMove(int drow, int dcol) {
	return drow == dcol && drow > 0;
}

// Change is L
bool ChessBoard::NMove(int drow, int dcol) {
	return (drow == 2 && dcol == 1) || (drow == 1 && dcol == 2);
}

// Change is along row XOR col; non-zero
bool ChessBoard::RMove(int drow, int dcol) {
	return (drow == 0 && dcol != 0) || (dcol == 0 && drow != 0);
}

// Either a Bishop or Rook move
bool ChessBoard::QMove(int drow, int dcol) {
	return BMove(drow, dcol) || RMove(drow, dcol);
}

// Pawn move, depends on take is involved
bool ChessBoard::PMove(int drow, int dcol, bool isWhite, int fromRow, bool take) {
	int dir = isWhite ? 1 : -1;
	int startRow = isWhite ? 1 : 6;

	// 1 forward on empty square
	if (!take && dcol == 0 && drow == dir) {
		return true;
	}
	// 2 forward from starting rank (mid square checked by clearPath)
	if (!take && dcol == 0 && drow == 2 * dir && fromRow == startRow) {
		return true;
	}
	// Diagonal capture only when taking an enemy piece
	if (take && my_abs(dcol) == 1 && drow == dir) {
		return true;
	}
	return false;
}

// Checks whether move is valid depending on piece
bool ChessBoard::validMovePiece(int drow, int dcol, char piece, int fromRow, bool take) {
	bool isWhite = (piece >= 'A' && piece <= 'Z');

	switch (piece) {
		case 'K': case 'k':
			return KMove(my_abs(drow), my_abs(dcol));
		case 'Q': case 'q':
			return QMove(my_abs(drow), my_abs(dcol));
		case 'B': case 'b':
			return BMove(my_abs(drow), my_abs(dcol));
		case 'N': case 'n':
			return NMove(my_abs(drow), my_abs(dcol));
		case 'R': case 'r':
			return RMove(my_abs(drow), my_abs(dcol));
		case 'P': case 'p':
			return PMove(drow, dcol, isWhite, fromRow, take);
		default:
			return false;
	}
}

// Is path clear?
bool ChessBoard::clearPath(Coordinate init, Coordinate dest, int drow, int dcol, char piece) const {
	// Uniformly converts to uppercase
	char upper = (piece >= 'a' && piece <= 'z')
		? static_cast<char>(piece - 'a' + 'A')
		: piece;

	// Kings and knights don't need path clear checks here
	if (upper == 'K' || upper == 'N') {
		return true;
	}
	// Pawns only have 1 intermediate square on a 2-step push
	if (upper == 'P') {
		if (my_abs(drow) <= 1) return true;
		int stepR = (drow > 0) ? 1 : -1;
		return grid[init.row + stepR][init.col] == '_';
	}

	// Rook, Bishop, and Queen walk strictly between init and dest
	int stepR = (drow > 0) ? 1 : ((drow < 0) ? -1 : 0);
	int stepC = (dcol > 0) ? 1 : ((dcol < 0) ? -1 : 0);

	int currR = init.row + stepR;
	int currC = init.col + stepC;

	while (currR != dest.row || currC != dest.col) {
		if (grid[currR][currC] != '_') {
			return false;
		}
		currR += stepR;
		currC += stepC;
	}

	return true;
}

// inCheck using predicted grid (returns true if moving piece leaves your own king in check)
bool ChessBoard::inCheck(Coordinate init, Coordinate dest, char piece) const {
	bool isWhite = (piece >= 'A' && piece <= 'Z');

	char testGrid[8][8];
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			testGrid[r][c] = grid[r][c];
		}
	}

	// Apply move on predicted grid
	testGrid[dest.row][dest.col] = piece;
	testGrid[init.row][init.col] = '_';

	// Locate own king
	char ownKing = isWhite ? 'K' : 'k';
	int kr = -1, kc = -1;
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			if (testGrid[r][c] == ownKing) {
				kr = r;
				kc = c;
				break;
			}
		}
	}
	if (kr == -1) return false;

	auto isEnemy = [&](char ch, char wSym, char bSym) {
		return ch == (isWhite ? bSym : wSym);
	};
	auto inBounds = [](int r, int c) {
		return r >= 0 && r < 8 && c >= 0 && c < 8;
	};

	// Knight attacks
	static const int kDr[8] = {2, 2, 1, 1, -1, -1, -2, -2};
	static const int kDc[8] = {1, -1, 2, -2, 2, -2, 1, -1};
	for (int i = 0; i < 8; ++i) {
		int r = kr + kDr[i], c = kc + kDc[i];
		if (inBounds(r, c) && isEnemy(testGrid[r][c], 'N', 'n')) return true;
	}

	// Pawn attacks
	int pawnStepR = isWhite ? 1 : -1;
	for (int dcStep : {-1, 1}) {
		int r = kr + pawnStepR, c = kc + dcStep;
		if (inBounds(r, c) && isEnemy(testGrid[r][c], 'P', 'p')) return true;
	}

	// Straight rays (Rook / Queen)
	static const int oDr[4] = {1, -1, 0, 0};
	static const int oDc[4] = {0, 0, 1, -1};
	for (int d = 0; d < 4; ++d) {
		int r = kr + oDr[d], c = kc + oDc[d];
		while (inBounds(r, c)) {
			char ch = testGrid[r][c];
			if (ch != '_') {
				if (isEnemy(ch, 'R', 'r') || isEnemy(ch, 'Q', 'q')) return true;
				break;
			}
			r += oDr[d];
			c += oDc[d];
		}
	}

	// Diagonal rays (Bishop / Queen)
	static const int dDr[4] = {1, 1, -1, -1};
	static const int dDc[4] = {1, -1, 1, -1};
	for (int d = 0; d < 4; ++d) {
		int r = kr + dDr[d], c = kc + dDc[d];
		while (inBounds(r, c)) {
			char ch = testGrid[r][c];
			if (ch != '_') {
				if (isEnemy(ch, 'B', 'b') || isEnemy(ch, 'Q', 'q')) return true;
				break;
			}
			r += dDr[d];
			c += dDc[d];
		}
	}

	// Adjacent enemy king
	for (int drStep = -1; drStep <= 1; ++drStep) {
		for (int dcStep = -1; dcStep <= 1; ++dcStep) {
			if (drStep == 0 && dcStep == 0) continue;
			int r = kr + drStep, c = kc + dcStep;
			if (inBounds(r, c) && isEnemy(testGrid[r][c], 'K', 'k')) return true;
		}
	}

	return false;
}

bool ChessBoard::boardSideChecks(const std::string& moveFrom, const std::string& moveTo, char piece) {
	Coordinate init = convertCoordinate(moveFrom);
	Coordinate dest = convertCoordinate(moveTo);

	int drow = dest.row - init.row;
	int dcol = dest.col - init.col;
	bool take = (grid[dest.row][dest.col] != '_');

	// Returns true only when move is valid and does NOT leave own king in check
	return validMovePiece(drow, dcol, piece, init.row, take) &&
	       clearPath(init, dest, drow, dcol, piece) &&
	       !inCheck(init, dest, piece);
}
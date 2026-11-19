#include <iostream>
#include <string>

struct Coordinate {
	int row;
	int col;
};

class ChessBoard {
	char grid[8][8];
	
	// This will convert coordinates from a4, c3, etc to numerical [x][y]
	Coordinate convertCoordinate(const std::string& input) const;
		
public:
	ChessBoard();
	// void print(); // Or the << operator overide?
	friend std::ostream& operator<<(std::ostream& os, const ChessBoard& board); // Either this or the above
	void resetSlot(const std::string& coord);
	char getSlot(const std::string& input) const; // input can be a4, c3, etc...
	void moveToSlot(const std::string& init, const std::string& dest); // Move a piece from initial coordinates to destination coordinates
};

// Initializes the ChessBoard
ChessBoard::ChessBoard() {
	// The following is temporary as there is the setup option that can overide this
    const char startRows[8][8] = {
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

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            grid[row][col] = startRows[row][col];
        }
    }
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

// Reset a coordinate to have nothing
void ChessBoard::resetSlot(const std::string& coord) {
	Coordinate curr = convertCoordinate(coord);
	
	grid[curr.row][curr.col] = '_';
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
	Coordinate destination = convertCoordinate(dest);
	
	char piece = getSlot(init);
	resetSlot(init);
	grid[destination.row][destination.col] = piece;
}

int main() {
	ChessBoard genericBoard;
	std::cout << genericBoard;
	
	return 0;
}
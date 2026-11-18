#include <iostream>
#include <string>
#include <ostream>

class ChessBoard {
	char grid[8][8];
		
public:
	ChessBoard();
	void print(); // Or the << operator overide?
	friend std::ostream& operator<<(std::ostream& os, const ChessBoard& board); // Either this or the above
	char returnSlot(int row, int col); // Will be called by above function to after decoding a4 into numeric coordinates
	char getSlot(std::string input); // input can be a4, c3, etc...
	void moveToSlot(int row_init, int col_init, int row_dest, int col_dest);
};

char ChessBoard::returnSlot(int row, int col) {
	return grid[row][col];
}

char ChessBoard::getSlot(std::string input) {
	// The function is primitive and does not check if input is valid
	char colLetter = input[0]; // According to diagram on assignment, the letter is along the bottom, so it is col
	int rowLetter = input[1] - '0';
	int col = colLetter - 'a'; // Convert letter to corresponding col
	int row = 8 - rowLetter;
	
	return returnSlot(row, col);
	// Wait, we can just do return grid[row][col]?
}

int main() {
	ChessBoard genericBoard;
	std::cout << genericBoard;
	
	return 0;
}
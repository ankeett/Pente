#include "Board.h"


using namespace std;


void Board::printBoard(char symbol) {
    // Print column labels (A - S)
    std::cout << "   ";
    for (char col = 'A'; col <= 'S'; col++) {      
        std::cout << col << "  ";
    }
    std::cout << "\n";

    // Print the board with row labels (1 - 19)
    for (int row = 18; row >= 0; row--) {  // Rows go from 1 to 19, so we start from 18 down to 0
        std::cout << setw(2) << row + 1 << ' '; // Set the width to 2 for row labels
        for (int col = 0; col < 19; col++) {
            if (board[row][col] == 0) {
                std::cout << ".  "; // Empty cell
            }
            else if (board[row][col] == 1) {
                std::cout << symbol<<"  "; // Player's stone
            }
            else {
                if(symbol == 'W')
                    std::cout << "B  "; // Computer's stone
				else
                    std::cout << "W  "; 
            }
        }
        std::cout << "\n";
    }
}

bool Board::isEmptyCell(int row, int col) const {
	return board[row-1][col] == 0;
}


//bool Board::isValidMove(string move) {
//    if (move.length() < 2) {
//        cout << "Invalid input.Please enter a valid position(e.g., K10) :" << endl;
//        return false;
//    }
//
//    if (move.length() > 4) {
//        cout << "Invalid input.Please enter a valid position(e.g., K10) : " << endl;
//        return false;
//    }
//    // Convert the entire string to lowercase using a loop
//
//    if (move.length() == 4) {
//
//        for (char& c : move) {
//            c = std::tolower(c);
//        }
//
//
//        if (move == "help") {
//            cout << "Need Help" << endl;
//            //Ask for help
//        }
//
//        if (move == "quit") {
//		    cout << "Quitting the game" << endl;
//		    //Quit the game
//            //save the game
//	    }
//
//    }
//    char colChar = toupper(move[0]); // Convert first character to uppercase
//    int row = std::stoi(move.substr(1)); // Convert row number and adjust to 0-based
//    int col = colChar - 'A'; // Convert column character to index
//
//    if (row >= 0 && row < 19 && col >= 0 && col < 19 && board[row-1][col] == 0) {
//        // Valid move
//        // Now you can use 'row' and 'col' to make the move on the board
//
//        return true;
//    }
//    else {
//        std::cout << "Invalid move. Please enter a valid position." << std::endl;
//        return false;
//    }
//    return true;
//}

void Board::placeStone(string move,char symbol) {
    char colChar = toupper(move[0]); // Convert first character to uppercase
	int row = std::stoi(move.substr(1)); // Convert row number and adjust to 0-based
	int col = colChar - 'A'; // Convert column character to index

    //place the stone on the board according to the human and computer player's move
    if (symbol == 'H') {
	    board[row - 1][col] = 1; 
    }
    else {
        board[row - 1][col] = 2;
    }
}
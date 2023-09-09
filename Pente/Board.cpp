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

//bool Board::checkFive(int row, int col, int symbol) {
//    //in board 1 is human player and 2 is computer player
//
//    /*cout<<"row"<<row<<"col"<<col<<"symbol"<<symbol<<endl;
//
//    cout<<"board[row-1][col]"<<board[row-1][col]<<endl;*/
//    // Check for five consecutive stones in different directions
//    if (checkDirection(row, col, symbol, -1, 0) ||   // Check left
//        checkDirection(row, col, symbol, 1, 0) ||    // Check right
//        checkDirection(row, col, symbol, 0, -1) ||   // Check up
//        checkDirection(row, col, symbol, 0, 1) ||    // Check down
//        checkDirection(row, col, symbol, -1, -1) ||  // Check up-left
//        checkDirection(row, col, symbol, -1, 1) ||   // Check up-right
//        checkDirection(row, col, symbol, 1, -1) ||   // Check down-left
//        checkDirection(row, col, symbol, 1, 1)) {    // Check down-right
//
//
//        if (symbol == 1) {
//            setWinner(1);
//		}
//		else {
//			setWinner(2);
//		}
//        return true; // Five consecutive stones found, game is won
//    }
//
//   
//
//    return false; // No five consecutive stones found
//}

//bool Board::checkFive(int row, int col, int symbol) {
//    //in board 1 is human player and 2 is computer player
//
//    /*cout<<"row"<<row<<"col"<<col<<"symbol"<<symbol<<endl;
//
//    cout<<"board[row-1][col]"<<board[row-1][col]<<endl;*/
//    // Check for five consecutive stones in different directions
//    if (checkDirection(row, col, symbol, -1, 0) ||   // Check left
//        checkDirection(row, col, symbol, 1, 0) ||    // Check right
//        checkDirection(row, col, symbol, 0, -1) ||   // Check up
//        checkDirection(row, col, symbol, 0, 1) ||    // Check down
//        checkDirection(row, col, symbol, -1, -1) ||  // Check up-left
//        checkDirection(row, col, symbol, -1, 1) ||   // Check up-right
//        checkDirection(row, col, symbol, 1, -1) ||   // Check down-left
//        checkDirection(row, col, symbol, 1, 1)) {    // Check down-right
//
//
//        if (symbol == 1) {
//            setWinner(1);
//        }
//        else {
//            setWinner(2);
//        }
//        return true; // Five consecutive stones found, game is won
//    }
//
//
//
//    return false; // No five consecutive stones found
//}
//
//bool Board::checkDirection(int row, int col, int symbol, int deltaRow, int deltaCol) {
//    int consecutiveStones = 0;
//
//    while (consecutiveStones < 5) {
//        row += deltaRow;
//        col += deltaCol;
//
//        if (row < 0 || row >= 19 || col < 0 || col >= 19 || board[row - 1][col] != symbol) {
//            break; // Stone not of the same symbol or out of bounds
//        }
//
//        consecutiveStones++;
//    }
//
//
//    return consecutiveStones == 4; // True if five consecutive stones are found
//}


bool Board::checkFive(int row, int col, int symbol) {
    int consecutiveSum = 0;

    // Check for five consecutive stones in vertical direction (up and down)
    consecutiveSum += checkDirection(row, col, symbol, 0, -1); // Check up
    consecutiveSum += checkDirection(row, col, symbol, 0, 1);  // Check down

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in horizontal direction (left and right)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, 0); // Check left
    consecutiveSum += checkDirection(row, col, symbol, 1, 0);  // Check right

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in diagonal direction (left-up and right-down)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, -1); // Check left-up
    consecutiveSum += checkDirection(row, col, symbol, 1, 1);   // Check right-down

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in diagonal direction (left-down and right-up)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, 1);  // Check left-down
    consecutiveSum += checkDirection(row, col, symbol, 1, -1);  // Check right-up

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    return false; // No five consecutive stones found
}

int Board::checkDirection(int row, int col, int symbol, int deltaRow, int deltaCol) {
    int consecutiveStones = 0;
    int r = row;
    int c = col;

    while (consecutiveStones < 4) {
        r += deltaRow;
        c += deltaCol;

        if (r < 0 || r >= 19 || c < 0 || c >= 19 || board[r-1][c] != symbol) {
            break; // Stone not of the same symbol or out of bounds
        }

        consecutiveStones++;
    }

    return consecutiveStones;
}





//check if the human player or computer player has captured the opponent's stone and remove it from the board
//TODO: check if the opponent's stone is captured and remove it from the board
bool Board::checkCapture(int row, int col, int symbol) {
	// Check for capture in different directions

	if (checkCaptureDirection(row, col, symbol, -1, 0) ||   // Check left
		checkCaptureDirection(row, col, symbol, 1, 0) ||    // Check right
		checkCaptureDirection(row, col, symbol, 0, -1) ||   // Check up
		checkCaptureDirection(row, col, symbol, 0, 1) ||    // Check down
		checkCaptureDirection(row, col, symbol, -1, -1) ||  // Check up-left
		checkCaptureDirection(row, col, symbol, -1, 1) ||   // Check up-right
		checkCaptureDirection(row, col, symbol, 1, -1) ||   // Check down-left
		checkCaptureDirection(row, col, symbol, 1, 1)) {    // Check down-right

        //save the captured count for the human and computer player
        if(symbol == 1)
			setHumanCaptures(getHumanCaptures() + 1);
		else
            setComputerCaptures(getComputerCaptures() + 1);

        
      
		return true; // Capture found
	}

	return false; // No capture found
}

//bool Board::checkCaptureDirection(int row, int col, int symbol, int deltaRow, int deltaCol) {
//    int opponentSymbol = (symbol == 1) ? 2 : 1; // Determine the opponent's symbol
//    int consecutiveOpponentStones = 0;
//    int totalOpponentStones = 0;
//
//    bool captured = false; // True if a capture is found
//
//    // Move one step in the specified direction
//    row += deltaRow;
//    col += deltaCol;
//
//     //Check for opponent's stones in the specified direction
//    while (consecutiveOpponentStones < 2) {
//        if (row < 0 || row >= 19 || col < 0 || col >= 19 || board[row][col] != opponentSymbol) {
//            break; // Stone not of the opponent's symbol or out of bounds
//        }
//
//        consecutiveOpponentStones++;
//        row += deltaRow;
//        col += deltaCol;
//    }
//
//    if (consecutiveOpponentStones == 2) {
//        captured = true;
//
//        //reset the board to empty cell
//        row -= deltaRow;
//        col -= deltaCol;
//
//        for (int i = 0; i < 2; i++) {
//			board[row][col] = 0;
//			row -= deltaRow;
//			col -= deltaCol;
//		}
//    }
//
//    return captured;
//}

bool Board::checkCaptureDirection(int row, int col, int symbol, int deltaRow, int deltaCol) {
    int opponentSymbol = (symbol == 1) ? 2 : 1; // Determine the opponent's symbol

    int consecutiveOpponentStones = 0;

    while (consecutiveOpponentStones < 2) {
        row += deltaRow;
        col += deltaCol;

        if (row < 0 || row >= 19 || col < 0 || col >= 19 || board[row-1][col] != opponentSymbol) {
            break; // Stone not of the opponent's symbol or out of bounds
        }

        consecutiveOpponentStones++;
    }

    if (consecutiveOpponentStones == 2) {
        // Two consecutive opponent stones found, now check for player's stone
        row += deltaRow;
        col += deltaCol;

        if (row >= 0 && row < 19 && col >= 0 && col < 19 && board[row-1][col] == symbol) {
            // Three stones in a row: opponent-opponent-player
            // Reset the board to empty cells for the two opponent stones
            row -= deltaRow * 2;
            col -= deltaCol * 2;

            for (int i = 0; i < 2; i++) {
                board[row-1][col] = 0;
                row += deltaRow;
                col += deltaCol;
            }

            return true; // Capture found
        }
    }

    return false; // No capture found
}


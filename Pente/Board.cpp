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
    consecutiveSum += checkDirection(row, col, symbol, 0, -1,5); // Check up
    consecutiveSum += checkDirection(row, col, symbol, 0, 1,5);  // Check down

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in horizontal direction (left and right)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, 0,5); // Check left
    consecutiveSum += checkDirection(row, col, symbol, 1, 0,5);  // Check right

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in diagonal direction (left-up and right-down)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, -1,5); // Check left-up
    consecutiveSum += checkDirection(row, col, symbol, 1, 1,5);   // Check right-down

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in diagonal direction (left-down and right-up)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, 1,5);  // Check left-down
    consecutiveSum += checkDirection(row, col, symbol, 1, -1,5);  // Check right-up

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    return false; // No five consecutive stones found
}

int Board::checkDirection(int row, int col, int symbol, int deltaRow, int deltaCol,int count) {
    int consecutiveStones = 0;
    int r = row-1;
    int c = col;

    count = count - 1;

    while (consecutiveStones < count) {
        r += deltaRow;
        c += deltaCol;

        if (r < 0 || r >= 19 || c < 0 || c >= 19 || board[r][c] != symbol) {
            break; // Stone not of the same symbol or out of bounds
        }

        consecutiveStones++;
    }

    return consecutiveStones;
}


bool Board::checkFour(int row, int col, int symbol) {
    int consecutiveSum = 0;

    // Check for five consecutive stones in vertical direction (up and down)
    consecutiveSum += checkDirection(row, col, symbol, 0, -1, 4); // Check up
    consecutiveSum += checkDirection(row, col, symbol, 0, 1, 4);  // Check down

    if (consecutiveSum >= 3) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in horizontal direction (left and right)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, 0, 4); // Check left
    consecutiveSum += checkDirection(row, col, symbol, 1, 0, 4);  // Check right

    if (consecutiveSum >= 3) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in diagonal direction (left-up and right-down)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, -1, 4); // Check left-up
    consecutiveSum += checkDirection(row, col, symbol, 1, 1, 4);   // Check right-down

    if (consecutiveSum >= 3) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in diagonal direction (left-down and right-up)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, 1, 4);  // Check left-down
    consecutiveSum += checkDirection(row, col, symbol, 1, -1, 4);  // Check right-up

    if (consecutiveSum >= 3) {
        setWinner(symbol);
        return true;
    }

    return false; // No five consecutive stones found
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

    row -= 1;

    while (consecutiveOpponentStones < 2) {
        row += deltaRow;
        col += deltaCol;

        if (row < 0 || row >= 19 || col < 0 || col >= 19 || board[row][col] != opponentSymbol) {
            break; // Stone not of the opponent's symbol or out of bounds
        }

        consecutiveOpponentStones++;
    }

    if (consecutiveOpponentStones == 2) {
        // Two consecutive opponent stones found, now check for player's stone
        row += deltaRow;
        col += deltaCol;

        if (row >= 0 && row < 19 && col >= 0 && col < 19 && board[row][col] == symbol) {
            // Three stones in a row: opponent-opponent-player
            // Reset the board to empty cells for the two opponent stones
            row -= deltaRow * 2;
            col -= deltaCol * 2;

            for (int i = 0; i < 2; i++) {
                board[row][col] = 0;
                row += deltaRow;
                col += deltaCol;
            }

            return true; // Capture found
        }
    }

    return false; // No capture found
}

int Board::calculateConsecutiveCount(int row, int col, int playerSymbol) {
    int consecutiveCount = 0;
    

    // Define directions for checking consecutive stones (horizontal, vertical, diagonal)
    const int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

    // Iterate through the four directions
    for (const auto& dir : directions) {
        int dirRow = dir[0];
        int dirCol = dir[1];

        // Check in both forward and backward directions
        for (int dirSign = -1; dirSign <= 1; dirSign += 2) {
            int count = 0;

            // Iterate in the current direction
            for (int step = 1; step <= 4; step++) { // Check up to 4 stones in a row
                int newRow = row + dirRow * dirSign * step;
                int newCol = col + dirCol * dirSign * step;

                // Check if the new position is within the board boundaries
                if (newRow >= 0 && newRow < 19 && newCol >= 0 && newCol < 19) {
                    if (board[newRow][newCol] == playerSymbol) {
                        count++;
                    }
                    else {
                        break; // Stop checking in this direction
                    }
                }
                else {
                    break; // Stop checking in this direction (out of bounds)
                }
            }

            // Update the consecutive count
            if (count > consecutiveCount) {
                consecutiveCount = count;
            }
        }
    }

    return consecutiveCount;
}
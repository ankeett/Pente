#include "Strategy.h"

Strategy::Strategy(Board& B, int playerSymbol) : board(B), playerSymbol(playerSymbol) {
    // Initialize other member variables or perform any necessary setup


}

Strategy::~Strategy() {
}



std::pair<int, int> Strategy::findWinningMove(Board B, int playerSymbol) {
    // Iterate through the entire game board
    for (int row = 0; row < 19; row++) {
        for (int col = 0; col < 19; col++) {
            // Check if the current cell is empty
            if (B.isEmptyCell(row,col)) {
                // Simulate placing the player's stone in the current empty cell
                B.setBoard(row, col, playerSymbol);

                // Check for five-in-a-row with the simulated stone
                if (B.checkFive(row,col,playerSymbol)) {
                    // If winning move is found, return the position
                    B.setBoard(row, col, 0); // Undo the simulation
                    return std::make_pair(row, col);
                }

                // Undo the simulation by resetting the cell to empty
                B.setBoard(row, col, 0);
            }
            else {
                cout<<"row: "<<row<<" col: "<<col<<" is not empty"<<endl;
            }
        }
    }

    // No immediate winning move found
    return std::make_pair(-1, -1); // Return a default value
}

std::pair<int, int> Strategy::defendWinningMove(Board B, int playerSymbol) {

    int opponentSymbol = (playerSymbol == 1) ? 2 : 1;

    // Iterate through the entire game board
    for (int row = 0; row < 19; row++) {
        for (int col = 0; col < 19; col++) {
			// Check if the current cell is empty
            if (B.isEmptyCell(row, col)) {
				// Simulate placing the player's stone in the current empty cell
				B.setBoard(row, col, opponentSymbol);

				// Check for five-in-a-row with the simulated stone
                if (B.checkFive(row, col, opponentSymbol)) {
					// If winning move is found, return the position
					B.setBoard(row, col, 0); // Undo the simulation
					return std::make_pair(row, col);
				}

				// Undo the simulation by resetting the cell to empty
				B.setBoard(row, col, 0);
			}
            else {
				cout<<"row: "<<row<<" col: "<<col<<" is not empty"<<endl;
			}
		}
	}

	// No immediate winning move found
	return std::make_pair(-1, -1); // Return a default value    
}

pair<int, int> Strategy::captureOpponent(Board B, int playerSymbol) {
    	int opponentSymbol = (playerSymbol == 1) ? 2 : 1;

	// Iterate through the entire game board
        for (int row = 0; row < 19; row++) {
            for (int col = 0; col < 19; col++) {
			// Check if the current cell is empty
                if (B.isEmptyCell(row, col)) {
				// Simulate placing the player's stone in the current empty cell
				B.setBoard(row, col, playerSymbol);

				// Check for five-in-a-row with the simulated stone
                if (B.checkCapture(row, col, playerSymbol)) {
					// If winning move is found, return the position
					B.setBoard(row, col, 0); // Undo the simulation
					return std::make_pair(row, col);
				}

				// Undo the simulation by resetting the cell to empty
				B.setBoard(row, col, 0);
			}
                else {
				cout<<"row: "<<row<<" col: "<<col<<" is not empty"<<endl;
			}
		}
	}

	// No immediate winning move found
	return std::make_pair(-1, -1); // Return a default value    

}

pair<int, int> Strategy::defendCapture(Board B, int playerSymbol) {

	int opponentSymbol = (playerSymbol == 1) ? 2 : 1;

	// Iterate through the entire game board
	for (int row = 0; row < 19; row++) {
		for (int col = 0; col < 19; col++) {
			// Check if the current cell is empty
			if (B.isEmptyCell(row, col)) {
				// Simulate placing the player's stone in the current empty cell
				B.setBoard(row, col, opponentSymbol);

				// Check for five-in-a-row with the simulated stone
				if (B.checkCapture(row, col, opponentSymbol)) {
					// If winning move is found, return the position
					B.setBoard(row, col, 0); // Undo the simulation
					return std::make_pair(row, col);
				}

				// Undo the simulation by resetting the cell to empty
				B.setBoard(row, col, 0);
			}
			else {
				cout<<"row: "<<row<<" col: "<<col<<" is not empty"<<endl;
			}
		}
	}

	// No immediate winning move found
	return std::make_pair(-1, -1); // Return a default value
}
pair<int, int> Strategy::evaluateAllCases(Board B, int playerSymbol) {

	//priority will be winning move, then defending win, then capturing opponent, then defending capture, then random
	pair<int, int> winningMove = findWinningMove(B, playerSymbol);
	if (winningMove.first != -1) {
		return winningMove;
	}

	pair<int, int> defendingWin = defendWinningMove(B, playerSymbol);
	if (defendingWin.first != -1) {
		return defendingWin;
	}

	pair<int, int> capturingOpponent = captureOpponent(B, playerSymbol);
	if (capturingOpponent.first != -1) {
		return capturingOpponent;
	}

	pair<int, int> defendingCapture = defendCapture(B, playerSymbol);
	if (defendingCapture.first != -1) {
		return defendingCapture;
	}

	return randomMove(B, playerSymbol);

}


pair<int, int> Strategy::randomMove(Board B, int playerSymbol) {
	int row = rand() % 19+1;
	int col = rand() % 19;
	while (!B.isEmptyCell(row, col)) {
		row = rand() % 19+1;
		col = rand() % 19;
	}
	return std::make_pair(row, col);
}


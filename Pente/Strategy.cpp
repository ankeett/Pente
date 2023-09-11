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
				continue;
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
				continue;
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
					continue;
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
				continue;
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
		cout<<"winning move"<<endl;
		return winningMove;
	}

	pair<int, int> defendingWin = defendWinningMove(B, playerSymbol);
	if (defendingWin.first != -1) {
		cout<<"defending win"<<endl;
		return defendingWin;
	}

	pair<int,int> defendingFour = defendFour(B, playerSymbol);
	if (defendingFour.first != -1) {
		cout<<"defending four"<<endl;
		return defendingFour;
	}

	pair<int, int> capturingOpponent = captureOpponent(B, playerSymbol);
	if (capturingOpponent.first != -1) {
		cout<<"capturing opponent"<<endl;
		return capturingOpponent;
	}

	pair<int, int> defendingCapture = defendCapture(B, playerSymbol);
	if (defendingCapture.first != -1) {
		cout<<"defending capture"<<endl;
		return defendingCapture;
	}

	pair<int,int> maxConsecutivePos = maxConsecutive(B, playerSymbol);
	if (maxConsecutivePos.first != -1) {
		cout<<"max consecutive"<<endl;
		return maxConsecutivePos;
	}

	pair<int, int> centerPos = controlCenter(B, playerSymbol);
	if (centerPos.first != -1) {
		cout<<"center"<<endl;
		return centerPos;
	}

	cout<<"random move"<<endl;
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


pair<int, int> Strategy::defendFour(Board B, int playerSymbol) {
	int opponentSymbol = (playerSymbol == 1) ? 2 : 1;


	// Iterate through the entire game board
	for (int row = 0; row < 19; row++) {
		for (int col = 0; col < 19; col++) {
			// Check if the current cell is empty
			if (B.isEmptyCell(row, col)) {
				// Simulate placing the player's stone in the current empty cell
				B.setBoard(row, col, opponentSymbol);

				// Check for five-in-a-row with the simulated stone
				if (B.checkFour(row, col, opponentSymbol)) {
					// If winning move is found, return the position
					B.setBoard(row, col, 0); // Undo the simulation
					return std::make_pair(row, col);
				}


				// Undo the simulation by resetting the cell to empty
				B.setBoard(row, col, 0);
			}
			else {
				continue;
			}
		}
	}

	// No immediate winning move found
	return std::make_pair(-1, -1); // Return a default value
}

//find the postion which has the most number of stones around it
pair<int, int> Strategy::maxConsecutive(Board B, int playerSymbol) {
	int maxConsecutiveCount = -1;  // Initialize to a negative value
	pair<int, int> bestPosition = make_pair(-1, -1); // Initialize to a default value

	// Iterate through the entire game board
	for (int row = 0; row < 19; row++) {
		for (int col = 0; col < 19; col++) {
			// Check if the current cell is empty
			if (B.isEmptyCell(row, col)) {
				// Calculate the maximum consecutive count around the current cell
				int consecutiveCount = B.calculateConsecutiveCount( row-1, col, playerSymbol);

				// Update the best position if a higher count is found
				if (consecutiveCount > maxConsecutiveCount) {
					maxConsecutiveCount = consecutiveCount;
					bestPosition = make_pair(row, col);
				}
			}
		}
	}
	// Return {-1, -1} if maxConsecutiveCount doesn't change
	if (maxConsecutiveCount <= 0) {
		return make_pair(-1, -1);
	}

	return bestPosition;
}

pair<int, int> Strategy::controlCenter(Board B, int playerSymbol) {
	// Define the coordinates of the center of the board
	int centerRow = 9;
	int centerCol = 9;

	// Check if the center is empty and return it if so
	if (B.isEmptyCell(centerRow, centerCol)) {
		return make_pair(centerRow, centerCol);
	}

	// If the center is not empty, search for the nearest empty cell around the center
	for (int radius = 1; radius < 5; radius++) { // Adjust the radius as needed
		for (int dr = -radius; dr <= radius; dr++) {
			for (int dc = -radius; dc <= radius; dc++) {
				int newRow = centerRow + dr;
				int newCol = centerCol + dc;

				// Check if the new position is within bounds and empty
				if (newRow >= 0 && newRow < 19 && newCol >= 0 && newCol < 19 &&
					B.isEmptyCell(newRow, newCol)) {
					return make_pair(newRow, newCol);
				}
			}
		}
	}

	// If no suitable position is found, return {-1, -1} to indicate no move is available
	return make_pair(-1, -1);
}




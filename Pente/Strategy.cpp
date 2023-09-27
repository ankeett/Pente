#include "Strategy.h"

Strategy::Strategy(Board& B, int playerSymbol) : board(B), playerSymbol(playerSymbol) {
    // Initialize other member variables or perform any necessary setup


}

Strategy::~Strategy() {
}


/*********************************************************************
Function Name: Strategy::findWinningMove
Purpose: Find a winning move for the given player symbol if one exists.
Parameters:
   - 'B' (Board object): The current game board state.
   - 'playerSymbol' (int): The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - A pair of integers representing the row and column of the winning move, or (-1, -1) if no immediate winning move is found.
Algorithm:
1. Iterate through the entire game board:
   a. For each empty cell, simulate placing the player's stone in the current empty cell.
   b. Check if the placement results in five-in-a-row for the player.
   c. If a winning move is found, return the position and undo the simulation.
   d. Otherwise, undo the simulation and continue to the next cell.
2. If no immediate winning move is found, return (-1, -1).
Assistance Received: None
*********************************************************************/
pair<int, int> Strategy::findWinningMove(Board B, int playerSymbol) {
    // Iterate through the entire game board
    for (int row = 1; row <= 19; row++) {
        for (int col = 0; col < 19; col++) {
            // Check if the current cell is empty
            if (B.isEmptyCell(row,col)) {
                // Simulate placing the player's stone in the current empty cell
                B.setBoard(row, col, playerSymbol);

                // Check for five-in-a-row with the simulated stone
                if (B.checkFive(row,col,playerSymbol)) {
                    // If winning move is found, return the position
                    B.setBoard(row, col, 0); 
                    return make_pair(row, col);
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
    return make_pair(-1, -1);
}

/*********************************************************************
Function Name: Strategy::defendWinningMove
Purpose: Find a move to defend against the opponent's potential winning move.
Parameters:
   - 'B' ( Board object): The current game board state.
   - 'playerSymbol'(int): The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - A pair of integers representing the row and column to defend against the opponent's potential winning move, or (-1, -1) if no immediate defensive move is found.
Algorithm:
1. Determine the opponent's symbol based on the player's symbol.
2. Iterate through the entire game board:
   a. For each empty cell, simulate placing the opponent's stone in the current empty cell.
   b. Check if the placement would result in a winning move for the opponent.
   c. If a potential winning move by the opponent is found, return the position to defend and undo the simulation.
   d. Otherwise, undo the simulation and continue to the next cell.
3. If no immediate defensive move is found, return (-1, -1) as a default value.
Assistance Received: None
*********************************************************************/
pair<int, int> Strategy::defendWinningMove(Board B, int playerSymbol) {

    int opponentSymbol = (playerSymbol == 1) ? 2 : 1;

    // Iterate through the entire game board
    for (int row = 1; row <= 19; row++) {
        for (int col = 0; col < 19; col++) {
			// Check if the current cell is empty
            if (B.isEmptyCell(row, col)) {
				// Simulate placing the player's stone in the current empty cell
				B.setBoard(row, col, opponentSymbol);

				// Check for five-in-a-row with the simulated stone
                if (B.checkFive(row, col, opponentSymbol)) {
					// If winning move is found, return the position
					B.setBoard(row, col, 0); // Undo the simulation
					return make_pair(row, col);
				}

				// Undo the simulation by resetting the cell to empty
				B.setBoard(row, col, 0);
			}
            else {
				continue;
			}
		}
	}

	// Return a default value    
	return make_pair(-1, -1); 
}

/*********************************************************************
Function Name: Strategy::captureOpponent
Purpose: Find a move that captures the most opponent stones from the current board state.
Parameters:
   - 'B' (Board object): The current game board state.
   - 'playerSymbol' (int): The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - A pair of integers representing the row and column to make a move that captures the most opponent stones, or (-1, -1) if no such move is found.
Algorithm:
1. Determine the opponent's symbol based on the player's symbol.
2. Create a map to keep track of the number of opponent stones that can be captured from each position.
3. Iterate through the entire game board:
   a. For each empty cell, simulate placing the player's stone in the current empty cell.
   b. Check for capturing opponent stones from the simulated placement. Repeat until no more captures are possible.
   c. If opponent stones can be captured, increment the count for that position in the map.
   d. Undo the simulation and continue to the next empty cell.
4. Find the position that can capture the most opponent stones by searching the map.
5. Return the position that can capture the most opponent stones, or (-1, -1) if no such move is found.
Assistance Received: None
*********************************************************************/
pair<int, int> Strategy::captureOpponent(Board B, int playerSymbol) {
    	int opponentSymbol = (playerSymbol == 1) ? 2 : 1;

		//keep track of the number of opponent stones that can be captured from a position
		//return the position that can capture the most number of opponent stones
		//keep rhe pair and the number of opponent stones that can be captured in a map

		map<pair<int, int>, int> captureMap;

	// Iterate through the entire game board
        for (int row = 1; row <= 19; row++) {
            for (int col = 0; col < 19; col++) {
			// Check if the current cell is empty
                if (B.isEmptyCell(row, col)) {
				// Simulate placing the player's stone in the current empty cell
				B.setBoard(row, col, playerSymbol);

				// Check for five-in-a-row with the simulated stone
                while (B.checkCapture(row, col, playerSymbol)) {
					// If winning move is found, return the position
					B.setBoard(row, col, 0); // Undo the simulation

					//increment the number of opponent stones that can be captured from this position
					auto it = captureMap.find(make_pair(row, col));
					if (it != captureMap.end()) {
						// Key exists in the map, increment the value
						it->second++;
					}
					else {
						// Key doesn't exist, so create it with a value of 1
						captureMap[make_pair(row, col)] = 1;
					}


					//return std::make_pair(row, col);
				}

				// Undo the simulation by resetting the cell to empty
				B.setBoard(row, col, 0);
			}
                else {
					continue;
				}
		}
	}

		//return the key with the highest value
		int max = -1;
		pair<int, int> bestPosition = make_pair(-1, -1);
		for (auto it = captureMap.begin(); it != captureMap.end(); it++) {
			if (it->second > max) {
				max = it->second;
				bestPosition = it->first;
			}
		}

	return bestPosition;

}

/*********************************************************************
Function Name: Strategy::defendCapture
Purpose: Find a move that defends against the opponent's capturing attempt by capturing the most opponent stones.
Parameters:
   - 'B' (Board object): The current game board state.
   - 'playerSymbol' (int): The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - A pair of integers representing the row and column to make a move that captures the most opponent stones as a defense, or (-1, -1) if no such move is found.
Algorithm:
1. Determine the opponent's symbol based on the player's symbol.
2. Create a map to keep track of the number of opponent stones that can be captured from each position while defending.
3. Iterate through the entire game board:
   a. For each empty cell, simulate placing the opponent's stone in the current empty cell.
   b. Check for capturing opponent stones from the simulated placement. Repeat until no more captures are possible.
   c. If opponent stones can capture your stones, increment the count for that position in the map.
   d. Undo the simulation and continue to the next empty cell.
4. Find the position that can capture the most stones  by searching the map.
5. Return the position that captures the most stones , or (-1, -1) if no such move is found.
Assistance Received: None
*********************************************************************/
pair<int, int> Strategy::defendCapture(Board B, int playerSymbol) {

	int opponentSymbol = (playerSymbol == 1) ? 2 : 1;
	map<pair<int, int>, int> captureMap;

	// Iterate through the entire game board
	for (int row = 1; row <= 19; row++) {
		for (int col = 0; col < 19; col++) {
			// Check if the current cell is empty
			if (B.isEmptyCell(row, col)) {
				// Simulate placing the player's stone in the current empty cell
				B.setBoard(row, col, opponentSymbol);

				// Check for five-in-a-row with the simulated stone
				while (B.checkCapture(row, col, opponentSymbol)) {
					// If winning move is found, return the position
					B.setBoard(row, col, 0); // Undo the simulation

					// increment the number of stones that can be captured from this position
					auto it = captureMap.find(make_pair(row, col));
					if (it != captureMap.end()) {
						// Key exists in the map, increment the value
						it->second++;
					}
					else {
						// Key doesn't exist, so create it with a value of 1
						captureMap[make_pair(row, col)] = 1;
					}

				}

				// Undo the simulation by resetting the cell to empty
				B.setBoard(row, col, 0);
			}
			else {
				continue;
			}
		}
	}
	//return the key with the highest value
	int max = -1;
	pair<int, int> bestPosition = make_pair(-1, -1);
	for (auto it = captureMap.begin(); it != captureMap.end(); it++) {
		if (it->second > max) {
			max = it->second;
			bestPosition = it->first;
		}
	}

	return bestPosition;
}

/*********************************************************************
Function Name: Strategy::evaluateAllCases
Purpose: Evaluate and prioritize different possible moves based on their importance and return the best move.
Parameters:
   - 'B' (Board object): The current game board state.
   - 'playerSymbol' (int): The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - A pair of integers representing the row and column of the best move based on evaluation, or rnadom Move if no suitable move is found.
Algorithm:
1. Evaluate potential moves in the following order of priority:
   a. Attempt to defend against the opponent's winning move.
   b. Attempt to defend against the opponent forming four in a row.
   c. Attempt to defend against the opponent capturing the player's stones.
   d. Attempt to capture opponent stones.
   e. Attempt to find a winning move.
   f. Attempt to make a move that maximizes consecutive stones.
   g. Attempt to control the center of the board.
   h. If none of the above moves is available, choose a random move.
2. Print the reason for selecting the chosen move.
3. Return the selected move.
Assistance Received: None
*********************************************************************/
pair<int, int> Strategy::evaluateAllCases(Board B, int playerSymbol) {

	//priority will be defending win, defending four, then defending capture, then capturing opponent, then winning move, then making max consecutive then trying to control the center, then randomizing the move
	pair<int, int> defendingWin = defendWinningMove(B, playerSymbol);
	if (defendingWin.first != -1) {
		cout<<"Reason: Defending win"<<endl;
		return defendingWin;
	}
	//int opponentSymbol = (playerSymbol == 1) ? 2 : 1;
	

	//if the player is winning and there is a good defense move, return it
	if  (getPlayerScore() > getOpponentScore()) {
		pair<int,int> defenseMove = evaluateDefense(B,playerSymbol);
		if (defenseMove.first != -1) {
			return defenseMove;
		}
	}

	pair<int,int> offenseMove = evaluateOffense(B,playerSymbol);
	//if no defense move is available, return the offense move or
	//if the player is losing and there is a good offense move, return it
	if (offenseMove.first != -1) {
		return offenseMove;
	}

	cout<<"Reason: No good position available. Randomizing the move."<<endl;
	return randomMove(B, playerSymbol);

}

pair<int, int> Strategy::evaluateOffense(Board B, int playerSymbol) {
	pair<int, int> capturingOpponent = captureOpponent(B, playerSymbol);
	if (capturingOpponent.first != -1) {
		cout << "Reason: Capturing opponent" << endl;
		return capturingOpponent;
	}

	//if no offense move is available, return the defense move
	pair<int,int> defenseMove = evaluateDefense(B,playerSymbol);
	if (defenseMove.first != -1) {
		return defenseMove;
	}

	pair<int, int> winningMove = findWinningMove(B, playerSymbol);
	if (winningMove.first != -1) {
		cout << "Reason: Winning move" << endl;
		return winningMove;
	}

	pair<int, int> maxConsecutivePos = maxConsecutive(B, playerSymbol);
	if (maxConsecutivePos.first != -1) {
		cout << "Reason: Trying to make Max consecutive" << endl;
		return maxConsecutivePos;
	}

	pair<int, int> centerPos = controlCenter(B, playerSymbol);
	if (centerPos.first != -1) {
		cout << "Reason: Trying to control the center." << endl;
		return centerPos;
	}

	return make_pair(-1, -1);
}

pair<int, int> Strategy::evaluateDefense(Board B, int playerSymbol) {

	pair<int, int> defendingCapture = defendCapture(B, playerSymbol);
	if (defendingCapture.first != -1) {
		cout << "Reason: Defending capture" << endl;
		return defendingCapture;
	}

	pair<int, int> defendingFour = defendFour(B, playerSymbol);
	if (defendingFour.first != -1) {
		cout << "Reason: Defending four" << endl;
		return defendingFour;
	}


	return make_pair(-1, -1);

}

/*********************************************************************
Function Name: Strategy::evaluateSecondMove
Purpose: Evaluate and prioritize a second move based on its importance and return the best move.
Parameters:
   - 'B' (Board object): The current game board state.
   - 'playerSymbol' (int): The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - A pair of integers representing the row and column of the best move based on evaluation, or random Move if no suitable move is found.
Algorithm:
1. Define the coordinates of the center of the board (centerRow, centerCol).
2. Search for an empty cell that is exactly 3 intersections away from the center (J10).
3. Evaluate the position based on the following criteria:
   - The new position is within bounds.
   - The new position is exactly 3 intersections away from the center.
   - The new position is empty.
4. If a suitable position is found, return it, and print the reason for the selection.
5. If no suitable position is found, return (-1, -1) to indicate no move is available, and print the reason as randomizing the move.
Assistance Received: None
*********************************************************************/
pair<int, int> Strategy::evaluateSecondMove(Board B, int playerSymbol) {

	// Define the coordinates of the center of the board
	int centerRow = 9;
	int centerCol = 9;

	// Search for an empty cell that is exactly 3 steps away from the center (J10)
	for (int dr = -2; dr <= 2; dr++) {
		for (int dc = -2; dc <= 2; dc++) {
			int newRow = centerRow + dr;
			int newCol = centerCol + dc;

			// Check if the new position is within bounds, exactly 3 intersections away, and empty
			if (newRow >= 0 && newRow < 19 && newCol >= 0 && newCol < 19 &&
				(dr * dr + dc * dc == 4) && B.isEmptyCell(newRow, newCol)) {
				cout << "Reason: 3 intersections away but closer to the center of the board" << endl;
				return make_pair(newRow, newCol);
			}
		}
	}

	// If no suitable position is found, return {-1, -1} to indicate no move is available
	cout << "Reason: No good position available. Randomizing the move." << endl;
	return randomMove(B, playerSymbol);
}



/*********************************************************************
Function Name: Strategy::randomMove
Purpose: Generate a random move by selecting an empty cell on the game board.
Parameters:
   - 'B' (Board object): The current game board state.
   - 'playerSymbol' (int): The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - A pair of integers representing the row and column of the randomly selected empty cell.
Algorithm:
1. Generate random row and column values within the range [1, 19] (inclusive).
2. Check if the selected cell is empty. If not, repeat the random selection until an empty cell is found.
3. Return the pair (row, col) of the randomly selected empty cell.
Assistance Received: None
*********************************************************************/
pair<int, int> Strategy::randomMove(Board B, int playerSymbol) {
	int row = rand() % 19+1;
	int col = rand() % 19;
	while (!B.isEmptyCell(row, col)) {
		row = rand() % 19+1;
		col = rand() % 19;
	}
	return make_pair(row, col);
}

/*********************************************************************
Function Name: Strategy::defendFour
Purpose: Defend against an opponent's potential four-in-a-row by finding a move that blocks it.
Parameters:
   - 'B' (Board object): The current game board state.
   - 'playerSymbol'(int): The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - A pair of integers representing the row and column of the position to block the opponent's potential four-in-a-row.
   - If no such move is found, returns {-1, -1} to indicate no defensive move is available.
Algorithm:
1. Determine the opponent's symbol based on the player's symbol.
2. Iterate through the entire game board to find empty cells.
3. Simulate placing the opponent's stone in each empty cell.
4. Check if this move creates a potential four-in-a-row for the opponent.
5. If a potential four-in-a-row is found, return the position (row, col) to block it.
6. Undo the simulation by resetting the cell to empty.
7. If no potential four-in-a-row is found, return {-1, -1} to indicate no defensive move is available.
Assistance Received: None
*********************************************************************/
pair<int, int> Strategy::defendFour(Board B, int playerSymbol) {
	int opponentSymbol = (playerSymbol == 1) ? 2 : 1;

	// Iterate through the entire game board
	for (int row = 1; row <= 19; row++) {
		for (int col = 0; col < 19; col++) {
			// Check if the current cell is empty
			if (B.isEmptyCell(row, col)) {
				// Simulate placing the player's stone in the current empty cell
				B.setBoard(row, col, opponentSymbol);

				// Check for five-in-a-row with the simulated stone
				if (B.checkFour(row, col, opponentSymbol)) {
					// If winning move is found, return the position
					B.setBoard(row, col, 0); // Undo the simulation
					return make_pair(row, col);
				}


				// Undo the simulation by resetting the cell to empty
				B.setBoard(row, col, 0);
			}
			else {
				continue;
			}
		}
	}

	return make_pair(-1, -1); // Return a default value
}

/*********************************************************************
Function Name: Strategy::maxConsecutive
Purpose: Find the position that has the most number of stones around it.
Parameters:
   - 'B' (Board object): The current game board state.
   - 'playerSymbol' (int): The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - A pair of integers representing the row and column of the position with the most consecutive stones around it.
   - If no such position is found, returns {-1, -1} to indicate that no move is available.
Algorithm:
1. Initialize 'maxConsecutiveCount' to a negative value and 'bestPosition' to a default position.
2. Iterate through the entire game board.
3. For each empty cell, calculate the maximum consecutive count of stones around it for the given player.
4. Update 'bestPosition' if a higher 'consecutiveCount' is found.
5. If 'maxConsecutiveCount' remains negative or zero, return {-1, -1} to indicate no move is available.
6. Return the 'bestPosition' with the most consecutive stones.
Assistance Received: None
*********************************************************************/
pair<int, int> Strategy::maxConsecutive(Board B, int playerSymbol) {
	int maxConsecutiveCount = -1;  
	pair<int, int> bestPosition = make_pair(-1, -1); 

	// Iterate through the entire game board
	for (int row = 1; row <= 19; row++) {
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

/*********************************************************************
Function Name: Strategy::controlCenter
Purpose: Find the position that allows control over the center of the board.
Parameters:
   - 'B' (Board object): The current game board state.
   - 'playerSymbol' (int): The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - A pair of integers representing the row and column of the position that provides control over the center.
   - If no such position is found, returns {-1, -1} to indicate that no move is available.
Algorithm:
1. Define the coordinates of the center of the board.
2. Check if the center is empty and return it if so.
3. If the center is not empty, search for the nearest empty cell around the center within a radius of 5.
4. Return the coordinates of the nearest empty cell that allows control over the center.
5. If no suitable position is found, return {-1, -1} to indicate no move is available.
Assistance Received: None
*********************************************************************/
pair<int, int> Strategy::controlCenter(Board B, int playerSymbol) {
	// Define the coordinates of the center of the board
	int centerRow = 9;
	int centerCol = 9;

	// Check if the center is empty and return it if so
	if (B.isEmptyCell(centerRow, centerCol)) {
		return make_pair(centerRow, centerCol);
	}

	// If the center is not empty, search for the nearest empty cell around the center
	for (int radius = 1; radius < 5; radius++) {
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
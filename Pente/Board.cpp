#include "Board.h"


using namespace std;

/* *********************************************************************
Function Name: Board::printBoard
Purpose: Print the Pente game board with the specified player's symbol.
Parameters:
   - 'symbol' (input): The symbol representing the human player's stones on the board.
Return Value: None
Algorithm:
1. Display column labels (A - S).
2. Iterate through each row and column of the board to print the contents.
   a. For each cell:
      - If the cell is empty (0), print a period ('.').
      - If the cell contains the player's stone (1), print the specified player's symbol.
      - If the cell contains the opponent's stone, print the opponent's symbol.
3. Repeat this process for all rows and columns, displaying the board with proper labels.
Assistance Received: None
********************************************************************* */
void Board::printBoard(char symbol) {
    // Print column labels (A - S)
    std::cout << "   ";
    for (char col = 'A'; col <= 'S'; col++) {      
        std::cout << col << "  ";
    }
    std::cout << "\n";

    // Print the board with row labels (1 - 19)
    // Rows go from 1 to 19, so we start from 18 down to 0
    for (int row = 18; row >= 0; row--) {  
        // Set the width to 2 for row labels
        std::cout << setw(2) << row + 1 << ' '; 
        for (int col = 0; col < 19; col++) {
            if (board[row][col] == 0) {
                std::cout << ".  ";
            }
            //player's stone
            else if (board[row][col] == 1) {
                std::cout << symbol<<"  "; 
            }
            else {
                if(symbol == 'W')
                    std::cout << "B  "; 
				else
                    std::cout << "W  "; 
            }
        }
        std::cout << "\n";
    }
}


/* *********************************************************************
Function Name: Board::placeStone
Purpose: Place a stone of the specified player on the game board at the specified position.
Parameters:
   - 'move': A string representing the player's move, with a column character and a row number (e.g., "A1").
   - 'symbol': The symbol representing the player ('H' for human, 'C' for computer).
Return Value: None
Algorithm:
1. Convert the first character of the 'move' string to uppercase, representing the column character.
2. Convert the row number from the 'move' string, adjusting to a 0-based index.
3. Convert the column character to an index.
4. Place the stone on the board according to the specified player's move:
   - If the player is human ('H'), place the stone with the value 1 on the board.
   - If the player is computer ('C'), place the stone with the value 2 on the board.
Assistance Received: None
********************************************************************* */
void Board::placeStone(string move,char symbol) {
    // Convert first character to uppercase
    char colChar = toupper(move[0]);
    // Convert row number and adjust to 0-based
	int row = std::stoi(move.substr(1));
    // Convert column character to index
	int col = colChar - 'A'; 

    //place the stone on the board according to the human and computer player's move
    if (symbol == 'H') {
	    board[row - 1][col] = 1; 
    }
    else {
        board[row - 1][col] = 2;
    }
}


/* *********************************************************************
Function Name: Board::checkFive
Purpose: Check if there are five consecutive stones of the specified player in any direction from a given position.
Parameters:
   - 'row': The row index where the check begins.
   - 'col': The column index where the check begins.
   - 'symbol': The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - 'true' if five consecutive stones are found in any direction, marking the player as the winner.
   - 'false' if no five consecutive stones are found.
Algorithm:
1. Initialize 'consecutiveSum' to 0.
2. Check for five consecutive stones in the vertical direction (up and down):
   a. Call 'checkDirection' to check for consecutive stones in the upward direction, incrementing 'consecutiveSum'.
   b. Call 'checkDirection' to check for consecutive stones in the downward direction, incrementing 'consecutiveSum'.
3. If 'consecutiveSum' is greater than or equal to 4 (indicating five consecutive stones), set the winner and return 'true'.
4. Reset 'consecutiveSum' to 0.
5. Check for five consecutive stones in the horizontal direction (left and right):
   a. Call 'checkDirection' to check for consecutive stones in the left direction, incrementing 'consecutiveSum'.
   b. Call 'checkDirection' to check for consecutive stones in the right direction, incrementing 'consecutiveSum'.
6. If 'consecutiveSum' is greater than or equal to 4, set the winner and return 'true'.
7. Reset 'consecutiveSum' to 0.
8. Check for five consecutive stones in diagonal directions (left-up, right-down, left-down, right-up):
   a. Call 'checkDirection' to check for consecutive stones in the left-up direction, incrementing 'consecutiveSum'.
   b. Call 'checkDirection' to check for consecutive stones in the right-down direction, incrementing 'consecutiveSum'.
   c. Call 'checkDirection' to check for consecutive stones in the left-down direction, incrementing 'consecutiveSum'.
   d. Call 'checkDirection' to check for consecutive stones in the right-up direction, incrementing 'consecutiveSum'.
9. If 'consecutiveSum' is greater than or equal to 4, set the winner and return 'true'.
10. If no five consecutive stones are found in any direction, return 'false'.
Assistance Received: None
********************************************************************* */
bool Board::checkFive(int row, int col, int symbol) {
    int consecutiveSum = 0;

    // Check for five consecutive stones in the vertical direction (up and down)
    consecutiveSum += checkDirection(row, col, symbol, 0, -1, 5); 
    consecutiveSum += checkDirection(row, col, symbol, 0, 1, 5);  

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in the horizontal direction (left and right)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, 0, 5); 
    consecutiveSum += checkDirection(row, col, symbol, 1, 0, 5); 

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in diagonal direction (left-up and right-down)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, -1, 5); 
    consecutiveSum += checkDirection(row, col, symbol, 1, 1, 5); 

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in diagonal direction (left-down and right-up)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, 1, 5); 
    consecutiveSum += checkDirection(row, col, symbol, 1, -1, 5);

    if (consecutiveSum >= 4) {
        setWinner(symbol);
        return true;
    }

    return false;
}

/* *********************************************************************
Function Name: Board::checkDirection
Purpose: Check for consecutive stones of the specified symbol in a given direction.
Parameters:
    - row (int): The row index of the starting position.
    - col (int): The column index of the starting position.
    - symbol (int): The symbol to check for consecutiveness.
    - deltaRow (int): The change in the row index to move in the specified direction.
    - deltaCol (int): The change in the column index to move in the specified direction.
    - count (int): The number of consecutive stones to check for.
Return Value: The number of consecutive stones of the specified symbol found in the given direction.

Algorithm:
    1. Initialize consecutiveStones to 0.
    2. Set r to the row one position before the starting row and c to the starting column.
    3. Decrement the count by 1.
    4. While consecutiveStones is less than the desired count:
        a. Move to the next position by adding deltaRow to r and deltaCol to c.
        b. Check if the new position (r, c) is out of bounds (r < 0, r >= 19, c < 0, c >= 19) or if the stone at board[r][c] is not equal to the specified symbol:
            i. If either condition is met, break out of the loop.
        c. Increment the consecutiveStones counter.
    5. Return the value of consecutiveStones.

Assistance Received: None
********************************************************************* */
int Board::checkDirection(int row, int col, int symbol, int deltaRow, int deltaCol,int count) {
    int consecutiveStones = 0;
    int r = row-1;
    int c = col;

    count = count - 1;

    while (consecutiveStones < count) {
        r += deltaRow;
        c += deltaCol;

        if (r < 0 || r >= 19 || c < 0 || c >= 19 || board[r][c] != symbol) {
            // Stone not of the same symbol or out of bounds
            break; 
        }

        consecutiveStones++;
    }

    return consecutiveStones;
}

/* *********************************************************************
Function Name: Board::checkFour
Purpose: Check if there are four consecutive stones of the specified player in any direction from a given position.
Parameters:
   - 'row': The row index where the check begins.
   - 'col': The column index where the check begins.
   - 'symbol': The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - 'true' if four consecutive stones are found in any direction.
   - 'false' if no four consecutive stones are found.
Algorithm:
1. Initialize 'consecutiveSum' to 0.
2. Check for four consecutive stones in the vertical direction (up and down):
   a. Call 'checkDirection' to check for consecutive stones in the upward direction, incrementing 'consecutiveSum'.
   b. Call 'checkDirection' to check for consecutive stones in the downward direction, incrementing 'consecutiveSum'.
3. If 'consecutiveSum' is greater than or equal to 3 (indicating four consecutive stones), return 'true'.
4. Reset 'consecutiveSum' to 0.
5. Check for four consecutive stones in the horizontal direction (left and right):
   a. Call 'checkDirection' to check for consecutive stones in the left direction, incrementing 'consecutiveSum'.
   b. Call 'checkDirection' to check for consecutive stones in the right direction, incrementing 'consecutiveSum'.
6. If 'consecutiveSum' is greater than or equal to 3, return 'true'.
7. Reset 'consecutiveSum' to 0.
8. Check for four consecutive stones in diagonal directions (left-up, right-down, left-down, right-up):
   a. Call 'checkDirection' to check for consecutive stones in the left-up direction, incrementing 'consecutiveSum'.
   b. Call 'checkDirection' to check for consecutive stones in the right-down direction, incrementing 'consecutiveSum'.
   c. Call 'checkDirection' to check for consecutive stones in the left-down direction, incrementing 'consecutiveSum'.
   d. Call 'checkDirection' to check for consecutive stones in the right-up direction, incrementing 'consecutiveSum'.
9. If 'consecutiveSum' is greater than or equal to 3, return 'true'.
10. If no four consecutive stones are found in any direction, return 'false'.
Assistance Received: None
********************************************************************* */

bool Board::checkFour(int row, int col, int symbol) {
    int consecutiveSum = 0;

    // Check for five consecutive stones in vertical direction (up and down)
    consecutiveSum += checkDirection(row, col, symbol, 0, -1, 4); // Check up
    consecutiveSum += checkDirection(row, col, symbol, 0, 1, 4);  // Check down

    if (consecutiveSum >= 3) {
        //setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in horizontal direction (left and right)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, 0, 4); // Check left
    consecutiveSum += checkDirection(row, col, symbol, 1, 0, 4);  // Check right

    if (consecutiveSum >= 3) {
        //setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in diagonal direction (left-up and right-down)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, -1, 4); // Check left-up
    consecutiveSum += checkDirection(row, col, symbol, 1, 1, 4);   // Check right-down

    if (consecutiveSum >= 3) {
        //setWinner(symbol);
        return true;
    }

    // Check for five consecutive stones in diagonal direction (left-down and right-up)
    consecutiveSum = 0;
    consecutiveSum += checkDirection(row, col, symbol, -1, 1, 4);  // Check left-down
    consecutiveSum += checkDirection(row, col, symbol, 1, -1, 4);  // Check right-up

    if (consecutiveSum >= 3) {
        //setWinner(symbol);
        return true;
    }

    return false; // No four consecutive stones found
}





/* *********************************************************************
Function Name: Board::checkCapture
Purpose: Check if there is a capture of the opponent's stones in any direction from a given position.
Parameters:
   - 'row': The row index where the capture check begins.
   - 'col': The column index where the capture check begins.
   - 'symbol': The symbol representing the player ('1' for human, '2' for computer).
Return Value:
   - 'true' if a capture is found in any direction, updating the captured count for the corresponding player.
   - 'false' if no capture is found.
Algorithm:
1. Check for capture in different directions by calling 'checkCaptureDirection' for all possible directions.
2. If a capture is found in any direction:
   a. Increment the captured count for the corresponding player (human or computer).
3. If a capture is found, return 'true'.
4. If no capture is found in any direction, return 'false'.
Assistance Received: None
********************************************************************* */
bool Board::checkCapture(int row, int col, int symbol) {
	// Check for capture in different directions

	if (checkCaptureDirection(row, col, symbol, -1, 0) ||  
		checkCaptureDirection(row, col, symbol, 1, 0) ||   
		checkCaptureDirection(row, col, symbol, 0, -1) ||   
		checkCaptureDirection(row, col, symbol, 0, 1) ||   
		checkCaptureDirection(row, col, symbol, -1, -1) ||  
		checkCaptureDirection(row, col, symbol, -1, 1) ||   
		checkCaptureDirection(row, col, symbol, 1, -1) ||   
		checkCaptureDirection(row, col, symbol, 1, 1)) { 

        //save the captured count for the human and computer player
        if(symbol == 1)
			setHumanCaptures(getHumanCaptures() + 1);
		else
            setComputerCaptures(getComputerCaptures() + 1);

        
        // Capture found
		return true; 
	}
    // No capture found
	return false;
}

/* *********************************************************************
Function Name: Board::checkCaptureDirection
Purpose: Check if there is a capture of the opponent's stones in a specific direction from a given position.
Parameters:
   - 'row': The row index where the capture check begins.
   - 'col': The column index where the capture check begins.
   - 'symbol': The symbol representing the player ('1' for human, '2' for computer).
   - 'deltaRow': The change in row direction (1 for down, -1 for up, 0 for no change).
   - 'deltaCol': The change in column direction (1 for right, -1 for left, 0 for no change).
Return Value:
   - 'true' if a capture is found in the specified direction, updating the board to remove the captured opponent stones.
   - 'false' if no capture is found in the specified direction.
Algorithm:
1. Determine the opponent's symbol based on the player's symbol.
2. Initialize 'consecutiveOpponentStones' to 0.
3. Decrement 'row' by 1 to start checking from the previous position.
4. While 'consecutiveOpponentStones' is less than 2:
   a. Update 'row' and 'col' based on 'deltaRow' and 'deltaCol'.
   b. If 'row' or 'col' is out of bounds or the stone at the position is not of the opponent's symbol, exit the loop.
   c. Increment 'consecutiveOpponentStones'.
5. If 'consecutiveOpponentStones' is equal to 2 (indicating two consecutive opponent stones):
   a. Update 'row' and 'col' to check for the player's stone.
   b. If the player's stone is found at the position:
      i. Remove the two opponent stones and the player's stone from the board.
      ii. Return 'true' to indicate a capture.
6. If no capture is found in the specified direction, return 'false'.
Assistance Received: None
********************************************************************* */
bool Board::checkCaptureDirection(int row, int col, int symbol, int deltaRow, int deltaCol) {
    // Determine the opponent's symbol
    int opponentSymbol = (symbol == 1) ? 2 : 1;

    int consecutiveOpponentStones = 0;

    row -= 1;

    while (consecutiveOpponentStones < 2) {
        row += deltaRow;
        col += deltaCol;

        if (row < 0 || row >= 19 || col < 0 || col >= 19 || board[row][col] != opponentSymbol) {
            // Stone not of the opponent's symbol or out of bounds
            break; 
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
            // Capture found
            return true;
        }
    }
    // No capture found
    return false;
}


/* *********************************************************************
Function Name: Board::calculateConsecutiveCount
Purpose: Calculate the maximum number of consecutive stones of a player in any direction from a given position.
Parameters:
   - 'row': The row index where the calculation begins.
   - 'col': The column index where the calculation begins.
   - 'playerSymbol': The symbol representing the player ('1' for human, '2' for computer).
Return Value: The maximum number of consecutive stones found in any direction.
Algorithm:
1. Initialize 'consecutiveCount' to 0.
2. Define four directions for checking consecutive stones: horizontal, vertical, and two diagonal directions.
3. Iterate through the four directions using a loop:
   a. For each direction, calculate the direction in terms of 'dirRow' and 'dirCol'.
   b. Check in both forward and backward directions.
   c. Initialize 'count' to 0.
   d. Iterate up to 4 steps to check for consecutive stones in the current direction.
   e. For each step, calculate the new position based on 'dirRow', 'dirCol', 'dirSign', and 'step'.
   f. Check if the new position is within the board boundaries:
      i. If the stone at the new position has the same symbol as the player, increment 'count'.
      ii. If the stone at the new position has a different symbol, break the loop to stop checking in this direction.
      iii. If the new position is out of bounds, break the loop to stop checking in this direction.
   g. Update 'consecutiveCount' with the maximum 'count' found in all directions.
4. Return 'consecutiveCount' as the result.
Assistance Received: None
********************************************************************* */
int Board::calculateConsecutiveCount(int row, int col, int playerSymbol) {
    int consecutiveCount = 0;
    
    // Define directions for checking consecutive stones (horizontal, vertical, diagonal)
    int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
   
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
                        // Stop checking in this direction
                        break; 
                    }
                }
                else {
                    // Stop checking in this direction (out of bounds)
                    break; 
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


/* *********************************************************************
Function Name: Board::countFour
Purpose: Count the number of occurrences of four consecutive stones of a player in any direction on the board.
Parameters:
   - 'symbol': The symbol representing the player ('1' for human, '2' for computer).
Return Value: The count of occurrences of four consecutive stones.
Algorithm:
1. Initialize 'count' to 0.
2. Define directions for all eight possible directions (up, down, left, right, and diagonals).
3. Create a copy of the board to mark cells found in four in a row.
4. Copy the current game board into 'copyBoard'.
5. Iterate through all rows and columns on the board using nested loops.
6. For each position on the board, iterate through all eight directions.
   a. For each direction, calculate the change in row ('dr') and column ('dc').
   b. Check for consecutive stones in the current direction using 'consecutiveSum'.
   c. For up to five stones (to identify game completion), check if each stone in the current direction matches 'symbol'.
   d. If a consecutive sum of four is found, increment 'count' and mark the cells in the 'copyBoard' as 0.
7. Repeat the process for all positions on the board and all directions.
8. Return the 'count' as the result, representing the count of occurrences of four consecutive stones.
Assistance Received: None
********************************************************************* */
int Board::countFour(int symbol) {
    int count = 0;

    // Define directions for all eight possible directions (up, down, left, right, and diagonals)
    int directions[][2] = {
        {0, -1},  // Up
        {0, 1},   // Down
        {-1, 0},  // Left
        {1, 0},   // Right
        {-1, -1}, // Left-Up
        {1, 1},   // Right-Down
        {-1, 1},  // Left-Down
        {1, -1}   // Right-Up
    };

    // Create a copy of the board to mark cells found in four in a row
    int copyBoard[19][19] = { 0 };
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            copyBoard[i][j] = board[i][j];
        }
    }

    for (int row = 0; row < 19; row++) {
        for (int col = 0; col < 19; col++) {
            for (int dir = 0; dir < 8; dir++) {
                int dr = directions[dir][0];
                int dc = directions[dir][1];

                // Check for consecutive stones in the current direction
                int consecutiveSum = 0;
                // Check five stones to identify game completion
                for (int i = 0; i < 5; i++) {
                    int newRow = row + i * dr;
                    int newCol = col + i * dc;

                    if (newRow >= 0 && newRow < 19 && newCol >= 0 && newCol < 19 && copyBoard[newRow][newCol] == symbol) {
                        consecutiveSum++;
                    } else {
                        // Reset the count if a non-symbol stone is encountered or if out of bounds
                        consecutiveSum = 0; 
                    }

                    if (consecutiveSum == 4) {
                        count++;
                        // Mark the cells in the copy as 0
                        for (int j = 0; j < 4; j++) {
                            int markRow = row + j * dr;
                            int markCol = col + j * dc;
                            copyBoard[markRow][markCol] = 0;
                        }
                    }
                }
            }
        }

    }

    return count;
}
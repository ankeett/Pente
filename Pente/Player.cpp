#include "Player.h"

Player::Player( char symbol) :  symbol(symbol) {

}

Player::~Player() {}

char Player::getSymbol() const {
    return symbol;
}
void Player::setSymbol(char newSymbol) {
    symbol = newSymbol;
}

HumanPlayer::HumanPlayer(char symbol): Player(symbol) {

}

HumanPlayer::~HumanPlayer() {
    // Default destructor is sufficient
}

ComputerPlayer::~ComputerPlayer() {
    // Default destructor is sufficient
}


/*********************************************************************
Function Name: HumanPlayer::makeMove
Purpose: Allows the human player to make a move in the game.
Parameters:
   - 'B' ( Board object by reference): The current game board state.
   - 'moveCount' ( int): The count of the current move (1 for the first move, 2 for the second move, etc.).
Return Value: None (void)
Algorithm:
1. Define a regular expression pattern to validate the format of the player's move input.
2. Use a do-while loop to repeatedly prompt the player for a valid move.
3. If it's the first move (moveCount == 1), the center of the board is automatically selected (J10).
4. For subsequent moves (moveCount > 1), the player is prompted to enter their move in the format "A1" to "S19".
5. The player's input is converted to uppercase, and various input validation checks are performed:
   - If the input is "HELP," a move hint is provided using the game's strategy.
   - If the input is "QUIT," the game is quit, and the player hasQuit status is set to true.
   - The input is validated against the movePattern regular expression to ensure it matches the expected format.
   - If the move doesn't match the format, an error message is displayed, and the player is prompted again.
6. The player's move is converted to row and column indices for the game board.
7. The `isValidMove` function is used to check if the move is valid (e.g., not out of bounds and the cell is empty).
8. If the move is valid, the stone is placed on the board, and the board is printed.
9. If the player wins with this move (forming five in a row), the game ends.
10. If the player captures opponent stones, this is displayed, and the loop continues.
11. If the move is invalid, an error message is displayed, and the player is prompted again until a valid move is entered.
12. The loop continues until the player enters a valid move.

Assistance Received: None
*********************************************************************/
void HumanPlayer::makeMove(Board& B, int moveCount) {
    regex movePattern("[A-S]([1-9]|1[0-9])");

    do {
        string move;
        if (moveCount == 1) {
            cout << "The first move is always in the center of the board." << endl;
            move = "J10";
        }
        else {
            cout << "Enter your move (e.g., K10):" << endl;
            cout<<"Enter HELP for a hint or QUIT for quitting the game."<<endl;

            cin >> move;
            for (char& c : move) c = toupper(c);

            if (move.length() < 2) {
                cout << "Invalid input.Please enter a valid position(e.g., K10) :" << endl;
                continue;
            }

            if (move.length() > 4) {
                cout << "Invalid input.Please enter a valid position(e.g., K10) : " << endl;
                continue;
            }

            if (move == "HELP") {
                Strategy strategy(B, 1);
                pair<int, int> bestCase;

                if(moveCount == 3){
					bestCase = strategy.evaluateSecondMove(B, 1);					
				}
                else {

                    bestCase = strategy.evaluateAllCases(B, 1);
                }


                cout << "The best move is " << (char)(bestCase.second + 'A') << (20-bestCase.first) << endl;

                cin.clear();
                cout << "Enter your move (e.g., K10):";
                cin >> move;

                for (char& c : move) c = toupper(c);

            }

            if (move == "QUIT") {
                cout << "Quitting the game" << endl;
                hasQuit(true);
                return;
            }


            //check if the input is valid
            if (!regex_match(move, movePattern)) {
			    cout << "Regex error. Invalid input.Please enter a valid position(e.g., K10) : " << endl;
			    continue;
		    }
        }



        if (moveCount == 3) {
			//the stone should be at least 3 intersections away from the center of the board ie J10
            if (!isThreePointsAway("J10", move)) {
				cout << "Invalid move. Please enter a valid position." << endl;
                cout<<"Hint: The stone should be at least 3 intersections away from the center of the board i.e. J10"<<endl;
				continue;
			}


        }

        // Convert first character to uppercase
        char colChar = move[0]; 
        // Convert row number and adjust to 0-based
        int row = 20- stoi(move.substr(1));
        // Convert column character to index
        int col = colChar - 'A';


        if (isValidMove(B, row, col)) {
            B.placeStone(move, 'H');
            B.printBoard(HumanPlayer::getSymbol());
            if (B.checkFive(row, col, 1)) {
				cout<<"You win!"<<endl;
                B.setGameOver(true);
                return;
            }

            while (B.checkCapture(row, col, 1)) {
                B.printBoard(HumanPlayer::getSymbol());
				cout<<"You captured a stone!"<<endl;
			}
            // Valid move, break out of the loop
            break;
        }
        else {
            cout << "Invalid move. Please enter a valid position." << endl;
        }
    } while (true);

    
    
}

/*********************************************************************
Function Name: Player::isThreePointsAway
Purpose: Checks if a given move is at least three intersections away from an initial position.
Parameters:
   - 'initialPos' (string): The position string representing the initial position.
   - 'nextPos' (string): The position string representing the next position to be checked.
Return Value:
   - 'true' if 'nextPos' is at least three intersections away from 'initialPos' in any direction.
   - 'false' otherwise.
Algorithm:
1. Convert the numeric parts of the position strings to integers to get row and column indices.
2. Calculate the absolute differences in rows and columns between 'initialPos' and 'nextPos'.
3. Check if the move is at least 3 intersections away in any direction:
   - If the absolute row difference is greater than or equal to 3.
   - If the absolute column difference is greater than or equal to 3.
   - If both row and column differences are greater than or equal to 3.
4. Return 'true' if the move meets any of these criteria; otherwise, return 'false.
Assistance Received: None
*********************************************************************/
bool Player::isThreePointsAway(string initialPos, string nextPos){
    // Convert the numeric parts of the positions to integers.
    int initialPosRow = std::stoi(initialPos.substr(1));
    int initialPosCol = initialPos[0] - 'A';

    int nextPosRow = std::stoi(nextPos.substr(1));
    int nextPosCol = nextPos[0] - 'A';

    // Calculate the absolute differences in rows and columns.
    int rowDifference = std::abs(initialPosRow - nextPosRow);
    int colDifference = std::abs(initialPosCol - nextPosCol);


    // Check if the move is at least 3 intersections away in any direction.
    return (rowDifference >= 3 || colDifference >= 3 || (rowDifference >= 3 && colDifference >= 3));
}

/*********************************************************************
Function Name: Player::isValidMove
Purpose: Checks if a move to a specified position on the game board is valid.
Parameters:
   - 'B' (Board object by const reference): The game board on which the move is to be checked.
   - 'row' (int): The row index of the position to check.
   - 'col' (int): The column index of the position to check.
Return Value:
   - 'true' if the move to the specified position is valid.
   - 'false' otherwise.
Algorithm:
1. Check if the 'row' is within the valid range (1 to 19) and 'col' is within the valid range (0 to 18).
2. Check if the cell at the specified 'row' and 'col' on the game board 'B' is empty (not occupied by any stone).
3. If both conditions are met, return 'true' to indicate a valid move; otherwise, return 'false'.
Assistance Received: None
*********************************************************************/
bool Player::isValidMove(const Board& B, int row, int col) const {
	return row >= 1 && row <= 19 && col >= 0 && col < 19 && B.isEmptyCell(row, col);
}



ComputerPlayer::ComputerPlayer( char symbol) : Player(symbol) {
}

/*********************************************************************
Function Name: ComputerPlayer::makeMove
Purpose: Makes a move for the computer player in the game.
Parameters:
   - 'B' (Board by reference): The game board on which the move is made.
   - 'moveCount' (int): The count of moves made in the game.
Return Value: None
Algorithm:
1. If 'moveCount' is 1, print a message indicating that the first move is always in the center of the board and set 'move' to "J10".
2. If 'moveCount' is not 1, create a 'Strategy' object for the computer player with 'B' and playerSymbol 2 (computer).
3. Determine the best move based on the game situation. If 'moveCount' is 3, ensure that the stone is at least 3 intersections away from the center of the board (J10).
4. Check if the determined move ('bestMove') is a valid move using the 'isValidMove' function.
5. If the move is valid, place the computer's stone on the board, print the move, and check for a win condition.
6. If a win condition is met, print the victory message and set the game as over.
7. If not, check if there are stones to be captured and print the appropriate message.
8. Repeat steps 1-7 until a valid move is made.

Assistance Received: None
*********************************************************************/
void ComputerPlayer::makeMove(Board& B, int moveCount) {
    do {
        string move;
        string showMove;
        int row, col;
        if (moveCount == 1) {
            cout << "The first move is always in the center of the board." << endl;
            move = "J10";
            row = 11;
            col = 10;
        }
        else {

            Strategy strategy(B,2);
            pair<int, int> bestMove;

            if (moveCount == 3){
                //the stone should be at least 3 intersections away from the center of the board ie J10
                bestMove = strategy.evaluateSecondMove(B, 2);

                
            }
            else {

                bestMove = strategy.evaluateAllCases(B, 2);
            }
            row = 20- bestMove.first;
            col = bestMove.second;

            char colChar = 'A' + col;

            //move is already changed in placeStone
            move = std::string(1, colChar) + std::to_string(row); 
            cout<<"move is "<<move<<endl;
            
            //row = 20- row;

            if (moveCount == 3) {
                if (!isThreePointsAway("J10", move)) {
                    continue;
                }
            }

        }
        row = 20- row;
        if (isValidMove(B, row, col)) {
            cout << "Computer's move: " << move << endl;
            B.placeStone(move, 'C');
            if (ComputerPlayer::getSymbol() == 'W') {
                B.printBoard('B');
            }
            else {
                B.printBoard('W');
            }


            if (B.checkFive(row, col, 2)) {
                cout << "Computer wins!" << endl;
                B.setGameOver(true);
                return;
            }

            //capturing two stones at the same time
            while (B.checkCapture(row, col, 2)) {
                if (ComputerPlayer::getSymbol() == 'W') {
                    B.printBoard('B');
                }
                else {
                    B.printBoard('W');
                }
                cout << "Computer captured a stone!" << endl;
            }

            // Break out of the loop
            break; 

        }
    } while (true);
}

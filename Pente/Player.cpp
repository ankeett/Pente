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



void HumanPlayer::makeMove(Board& B, int moveCount) {
    // Implement code to get input from the human player and make a move on the Pente board
    // You can prompt the player for input and handle their move here
    do {
        string move;
        if (moveCount == 1) {
            cout << "The first move is always in the center of the board." << endl;
            move = "J10";
        }
        else {
            cout << "Enter your move (e.g., K10):";
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
                cout << "The best move is " << (char)(bestCase.second + 'A') << bestCase.first << endl;

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

        }
        if (moveCount == 3) {
			//the stone should be at least 3 intersections away from the center of the board ie J10
            cout << "Here I am" << endl;
            if (!isThreePointsAway("J10", move)) {
				cout << "Invalid move. Please enter a valid position." << endl;
                cout<<"Hint: The stone should be at least 3 intersections away from the center of the board i.e. J10"<<endl;
				continue;
			}


        }



        char colChar = move[0]; // Convert first character to uppercase
        int row = std::stoi(move.substr(1)); // Convert row number and adjust to 0-based
        int col = colChar - 'A'; // Convert column character to index


        if (isValidMove(B, row, col)) {
            B.placeStone(move, 'H');
            B.printBoard(HumanPlayer::getSymbol());
            if (B.checkFive(row, col, 1)) {
				cout<<"You win!"<<endl;
                B.setGameOver(true);
                return;
            }

            if (B.checkCapture(row, col, 1)) {
                B.printBoard(HumanPlayer::getSymbol());
				cout<<"You captured a stone!"<<endl;
			}
            break; // Valid move, break out of the loop
        }
        else {
            cout << "Invalid move. Please enter a valid position." << endl;
        }
    } while (true);

    
    
}

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


bool Player::isValidMove(const Board& B, int row, int col) const {
	// Implement code to check if a move is valid
	// This function should return true if the move is valid and false otherwise
	// Implement the move validation logic

	return row >= 1 && row <= 19 && col >= 0 && col < 19 && B.isEmptyCell(row, col);
}



ComputerPlayer::ComputerPlayer( char symbol) : Player(symbol) {
}

void ComputerPlayer::makeMove(Board& B, int moveCount) {
    // Implement an AI algorithm for the computer player's move
    // This function should generate a valid move for the computer
    // Implement the AI move logic

    

    do {
        string move;
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
            row = bestMove.first;
            col = bestMove.second;
            char colChar = 'A' + col; // Convert col to a character ('A' to 'S')
            move = std::string(1, colChar) + std::to_string(row); // Combine colChar and row

            if (moveCount == 3) {
                if (!isThreePointsAway("J10", move)) {
                    continue;
                }
            }

        }

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


            break; // Break out of the loop

        }
    } while (true);
}

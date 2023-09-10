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



void HumanPlayer::makeMove(Board& B) {
    // Implement code to get input from the human player and make a move on the Pente board
    // You can prompt the player for input and handle their move here
    do {

        string move;
        cout << "Enter your move (e.g., K10):";
        cin >> move;

        if (move.length() < 2) {
            cout << "Invalid input.Please enter a valid position(e.g., K10) :" << endl;
            return;
        }

        if (move.length() > 4) {
            cout << "Invalid input.Please enter a valid position(e.g., K10) : " << endl;
            return;
        }

        for (char& c : move) c = toupper(c);

        if (move == "HELP") {
            cout << "Help" << endl;
            //Ask for help
            return;
        }

        if (move == "QUIT") {
            cout << "Quitting the game" << endl;
            //Quit the game
            //save the game
            return;
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

bool Player::isValidMove(const Board& B, int row, int col) const {
	// Implement code to check if a move is valid
	// This function should return true if the move is valid and false otherwise
	// Implement the move validation logic

	return row >= 1 && row <= 19 && col >= 0 && col < 19 && B.isEmptyCell(row, col);
}



ComputerPlayer::ComputerPlayer( char symbol) : Player(symbol) {
}

void ComputerPlayer::makeMove(Board& B) {
    // Implement an AI algorithm for the computer player's move
    // This function should generate a valid move for the computer
    // Implement the AI move logic

    do {


        //int row, col;

        //row = rand() % 19 + 1;
        //col = rand() % 19;

        //// Convert the random row and col to a move string

        //call strategy
        //std::pair<int,int> bestMove =  getStrategy().findWinningMove(B, 2);

        //cout<<"Computer's move: "<<bestMove.first<<","<<bestMove.second<<endl;

        Strategy strategy(B,2);

        std::pair<int, int> bestMove = strategy.evaluateAllCases(B, 2);
        cout<<"Computer's move: "<<bestMove.first<<","<<bestMove.second<<endl;

        //string move;
        //cout << "Computer, Enter your move (e.g., K10):";
        //cin >> move;

        //for (char& c : move) c = toupper(c);

        //char colChar = move[0]; // Convert first character to uppercase
        //int row = std::stoi(move.substr(1)); // Convert row number and adjust to 0-based
        //int col = colChar - 'A'; // Convert column character to index

        int row = bestMove.first;
        int col = bestMove.second;

        char colChar = 'A' + col; // Convert col to a character ('A' to 'S')
        std::string move = std::string(1, colChar) + std::to_string(row); // Combine colChar and row

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

            if (B.checkCapture(row, col, 2)) {
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

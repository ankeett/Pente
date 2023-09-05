#include "Player.h"

Player::Player( char symbol) :  symbol(symbol) {}


char Player::getSymbol() const {
    return symbol;
}
void Player::setSymbol(char newSymbol) {
    symbol = newSymbol;
}

HumanPlayer::HumanPlayer(char symbol): Player(symbol) {}

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
            break;
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

ComputerPlayer::ComputerPlayer( char symbol) : Player(symbol) {}

void ComputerPlayer::makeMove(Board& B) {
    // Implement an AI algorithm for the computer player's move
    // This function should generate a valid move for the computer
    // Implement the AI move logic

    int row, col;

    row = rand() % 19 + 1;
    col = rand() % 19;

    // Convert the random row and col to a move string
    char colChar = 'A' + col; // Convert col to a character ('A' to 'S')
    std::string move = std::string(1, colChar) + std::to_string(row); // Combine colChar and row


    if (isValidMove(B, row, col)) {
        cout<<"Computer's move: "<<move<<endl;
        B.placeStone(move, 'C');
        if (ComputerPlayer::getSymbol() == 'W') {
            B.printBoard('B');
		}
        else {
			B.printBoard('W');
        }

    }
}

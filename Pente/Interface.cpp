#include "Interface.h"

//constructor
Interface::Interface() : human('W'), computer('B'){}

//Destructor
Interface::~Interface() {
	cout << "Game Over" << endl;
}

void Interface::startMenu() {

	cout << "Welcome to Pente" << endl;

    int option;

    do {
        cout << "Choose an option:" << endl;
        cout << " 1. Start the Game" << endl;
        cout << " 2. Continue the Game" << endl;
        cin >> option;
    } while (option != 1 && option != 2);

    if (option == 1) {
        startGame(B);
    }
    else {
		//Load the game
	}
}

void Interface::startGame(Board B) {
    cout << "Starting the Game" << endl;

    B.printBoard('W'); //Print the board with the column and row labels
    int option;
    
    do {
    cout << "Toss:" << endl;
    cout << "Choose 0 for Head and 1 for Tails" << endl;
    cin >> option;
    } while (option != 0 && option != 1);

    //Toss
    srand(time(0));
    int result = rand() % 2;
    char currentPlayer;

    if (option == result){
        cout << "You play white" << endl;
        currentPlayer = 'H';
        human.setSymbol('W');
        computer.setSymbol('B');
    }
    else {
        cout << "Computer plays white" << endl;
        currentPlayer = 'C';
        human.setSymbol('B');
        computer.setSymbol('W');
    }

    //Create a Player Class and handle the move from there
    while (true) {
        if (currentPlayer == 'H') {
            //Human's turn
            human.makeMove(B);
        }
        else {
            //Computer's turn
            //Implement the AI algorithm
            computer.makeMove(B);
        }
        //Check if the game is over

        //check if the human move was invalid 
        //if invalid, the human player gets another chance to make a move
        //if valid, the computer player makes a move

        //check if the computer move was invalid
        //if invalid, the computer player gets another chance to make a move
        //if valid, the human player makes a move

         




        currentPlayer = (currentPlayer == 'H') ? 'C' : 'H';
    }

}


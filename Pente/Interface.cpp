#include "Interface.h"

//constructor
Interface::Interface() {
    //Initialize player pointers
    playerList[0] = new HumanPlayer('W');
    playerList[1] = new ComputerPlayer('B');
    currentPlayerIndex = 0; //Start the game with human
}

//Destructor
Interface::~Interface() {
	//Delete player pointers
	delete playerList[0];
	delete playerList[1];
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
    //char currentPlayer;

    if (option != result){
        cout << "Computer Wins the Toss" << endl;
        cout << "You play Black" << endl;
        Player* temp = playerList[0];
        playerList[0] = playerList[1];
        playerList[1] = temp;
        
    }
    else {
        cout << "You win the Toss" << endl;
        cout << "You play White" << endl;
    }

    // Set player symbols
       playerList[0]->setSymbol('W');
       playerList[1]->setSymbol('B');

    // Create a Player pointer to handle the current player's move
    Player* currentPlayerPtr = playerList[currentPlayerIndex];

    //while the game is not over
    while (!B.isGameOver()) {
        // Player's turn
        currentPlayerPtr->makeMove(B);

        // Check if the game is over (implement this logic)

        // Switch to the other player's turn
        currentPlayerIndex = (currentPlayerIndex + 1) % 2;
        currentPlayerPtr = playerList[currentPlayerIndex];

    }

}


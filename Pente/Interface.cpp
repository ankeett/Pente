#include "Interface.h"

//constructor
Interface::Interface() {

}

//Destructor
Interface::~Interface() {

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



}

void Interface::startGame(Board B) {
    cout << "Starting the Game" << endl;

    B.printBoard();
    int option;
    
    do {
    cout << "Toss:" << endl;
    cout << "Choose 0 for Head and 1 for Tails" << endl;
    cin >> option;
    } while (option != 0 && option != 1);

    //Toss
    srand(time(0));
    int result = rand() % 2;
    int currentPlayer;

    if (option == result){
        cout << "You play white" << endl;
        currentPlayer = 1;
    }
    else {
        cout << "Computer plays white" << endl;
        currentPlayer = 2;
    }

    //Create a Player Class and handle the move from there


    


    
}


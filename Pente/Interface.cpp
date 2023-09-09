#include "Interface.h"

//constructor
Interface::Interface(Player* playerList[2]) {
    this->playerList[0] = playerList[0];
	this->playerList[1] = playerList[1];
}

//Destructor
Interface::~Interface() {

}

void Interface::startMenu() {

	cout<<"Round " << endl; 

    startGame(B);
}

void Interface::startGame(Board B) {
    cout << "Starting the Game" << endl;

    B.printBoard('W'); //Print the board with the column and row labels
    
    // Create a Player pointer to handle the current player's move
        int currentPlayerIndex;
        cout<<playerList[0]->getSymbol()<<endl;
       if(playerList[0]->getSymbol() == 'W')
		   currentPlayerIndex = 0;
	   else
		   currentPlayerIndex = 1;

    Player* currentPlayerPtr = playerList[currentPlayerIndex];

    //while the game is not over
    while (!B.isGameOver()) {
        // Player's turn
        currentPlayerPtr->makeMove(B);

        // Check if the game is over (implement this logic)

        // Switch to the other player's turn
        currentPlayerIndex = (currentPlayerIndex + 1) % 2;
        currentPlayerPtr = playerList[currentPlayerIndex];


        //check scores
       /* if (B.getWinner() != 0) {
			cout << "Game Over" << endl;
			cout << "Player " << B.getWinner() << " wins" << endl;
            break;
        }*/

        //calculate scores

        calculateScores(B);

		// Print the board
        printScores();

    }
}

void Interface :: calculateScores(Board& B) {
     if(B.getHumanCaptures() == 5 || B.getComputerCaptures() == 5){
			cout << "Game Over" << endl;
			if(B.getHumanCaptures() == 5)
				cout << "You win!" << endl;
			else
				cout << "Computer wins" << endl;
			B.setGameOver(true);
		}


        // Print the scores
        cout << "Human Captures: " << B.getHumanCaptures() << endl;
        cout << "Computer Captures: " << B.getComputerCaptures() << endl;

        setHumanScore(B.getHumanCaptures());
        setComputerScore(B.getComputerCaptures());

        if (B.getWinner() != 0) {
            if (B.getWinner() == 1) {
                setWinner(1);
                setHumanScore(getHumanScore() + 5);
            }
			else {
                setWinner(2);
				setComputerScore(getComputerScore() + 5);
        }
    }

}

void Interface::printScores() const{
    cout << "Human Score: " << getHumanScore() << endl;
    cout << "Computer Score: " << getComputerScore() << endl;
}

int Interface::sendWinner(Board& B) {
    //1 is human, 2 is computer
    return B.getWinner();
}
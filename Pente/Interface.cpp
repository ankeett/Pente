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
    B.printBoard('W'); //Print the board with the column and row labels
    startGame(B);
}

void Interface::continueMenu() {
	cout << "Continue the Game" << endl;
	continueGame(B);


}

void Interface::continueGame(Board& B) {
    Serialization s(B);
    s.readBoard(B);


    //set the players in the player list
    //the player with the white stone is the first player
    //the white stone is playerList[0]
    //the construtor has the playerList[0] as the human player
    //the constructor has the playerList[1] as the computer player
    //if the human player is white, then the human player is playerList[0]
    //if the human player is black, then the human player is playerList[1]

    if (s.getHumanColor() == 'W') {
		//player 1 is human
	}
    else {
		Player* temp = playerList[0];
        playerList[0] = playerList[1];
        playerList[1] = temp;
	}

    //set the symbol
    playerList[0]->setSymbol('W');
    playerList[1]->setSymbol('B');


    //set the scores and captures
    B.setHumanCaptures(s.getHumanCaptures());
    B.setComputerCaptures(s.getComputerCaptures());

    setHumanScore(s.getHumanScore());
    setComputerScore(s.getComputerScore());

    //get the scores and captures
    cout<< "Human Captures: " << B.getHumanCaptures() << endl;
    cout<< "Computer Captures: " << B.getComputerCaptures() << endl;

    cout<< "Human Score: " << getHumanScore() << endl;
    cout<< "Computer Score: " << getComputerScore() << endl;
    
    //find the next player and set the symbol
    startGame(B);

}

void Interface::startGame(Board& B) {
    
    // Create a Player pointer to handle the current player's move
        int currentPlayerIndex;
       if(playerList[0]->getSymbol() == 'W')
		   currentPlayerIndex = 0;
	   else
		   currentPlayerIndex = 1;

    Player* currentPlayerPtr = playerList[currentPlayerIndex];

    //while the game is not over
    while (!B.isGameOver()) {
        // Player's turn
        currentPlayerPtr->makeMove(B);

        //check if the currentPlayer wants to quit
        if (currentPlayerPtr->getQuit() == true) {
			quitGame(B);
            B.setGameOver(true);
			return;
		}
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

void Interface::quitGame(Board& B) {
	// Save the game
	Serialization s(B);
	s.writeIntoFile(B);

	// Print the scores
	

	// Announce the winner
	cout << "Player " << B.getWinner() << " wins" << endl;
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
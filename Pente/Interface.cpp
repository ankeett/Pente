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

    //set the move number
    B.setMoveCount(1);



}

void Interface::continueMenu() {
	cout << "Continue the Game" << endl;
    
	continueGame(B);



}

void Interface::continueGame(Board& B) {
    Serialization s(B);
    s.readBoard(B);
    //get the move count and set the move count
    int moveCount = B.checkEmptyBoard();
    B.setMoveCount(moveCount+1);

    //set the players in the player list
    //the player with the white stone is the first player
    //the white stone is playerList[0]
    //the construtor has the playerList[0] as the human player
    //the constructor has the playerList[1] as the computer player
    //if the human player is white, then the human player is playerList[0]
    //if the human player is black, then the human player is playerList[1]

    if (s.getHumanColor() == 'W') {
        //player 1 is human
        //if next player is human, then set index

        if (s.getNextPlayer() == "Human") {
            setCurrentPlayerIndex(0);
        }
        else {
            setCurrentPlayerIndex(1);
        }
    }
    else {
		Player* temp = playerList[0];
        playerList[0] = playerList[1];
        playerList[1] = temp;

        if (s.getNextPlayer() == "Human") {
            setCurrentPlayerIndex(1);
        }
        else {
            setCurrentPlayerIndex(0);
        }

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

    //check if the board is empty
    //send the move information in the board to the player
    //if the board is empty, the first player moves at the centeof the board
    //if the board is not empty, and the move is 3rd, place the stone 3 blocks away from the center
       

    
    // Create a Player pointer to handle the current player's move
        /*int currentPlayerIndex;
       if(playerList[0]->getSymbol() == 'W')
		   currentPlayerIndex = 0;
	   else
		   currentPlayerIndex = 1;*/

    Player* currentPlayerPtr = playerList[getCurrentPlayerIndex()];

    //while the game is not over
    while (!B.isGameOver()) {
        // Player's turn
        currentPlayerPtr->makeMove(B, B.getMoveCount());

        //check if the currentPlayer wants to quit
        if (currentPlayerPtr->getQuit() == true) {
            setQuit(true);
   //         cout<<"Do you want to serialize the game? (y/n)" << endl;
   //         char answer;
   //         cin >> answer;

   //         answer = tolower(answer);

   //         if (answer == 'y') {

   //             //quit the game and let the tournament class serialize the game
   //             

   //             serializeGame(B);
			//}
            B.setGameOver(true);
			return;
		}
        // Switch to the other player's turn
        //currentPlayerIndex = (currentPlayerIndex + 1) % 2;
        //currentPlayerPtr = playerList[currentPlayerIndex];

        setCurrentPlayerIndex((currentPlayerIndex +1) %2);
        currentPlayerPtr = playerList[getCurrentPlayerIndex()];

        B.setMoveCount(B.getMoveCount() + 1);

        // Print the scores
        cout << "Human Captures: " << B.getHumanCaptures() << endl;
        cout << "Computer Captures: " << B.getComputerCaptures() << endl;


        //check captures 
        if (B.getHumanCaptures() == 5 || B.getComputerCaptures() == 5) {
            cout << "Game Over" << endl;
            if (B.getHumanCaptures() == 5) {
                setWinner(1);
                cout << "You win!" << endl;
            }
            else {
                setWinner(2);
                cout << "Computer wins" << endl;

            }
            B.setGameOver(true);
        }

        //no need to ask if the current player is human

        if (currentPlayerPtr->getSymbol() != getHumanColor()) {
            cout<<"Do you want to quit?(y/n)" << endl;
            string response;
            cin >> response;
            for (char& r : response) r = toupper(r);

            if (response == "Y") {
			    cout << "Quitting the game" << endl;
			    setQuit(true);
                B.setGameOver(true);
			    return;
		    }
        }

    }


    //calculate scores
    calculateScores(B);

    //print scores
    printScores();

}

//void Interface::serializeGame(Board& B) {
//	// Save the game
//	Serialization s(B);
//    s.setComputerCaptures(B.getComputerCaptures());
//    s.setHumanCaptures(B.getHumanCaptures());   
//    s.setComputerScore(getComputerScore());
//    s.setHumanScore(getHumanScore());
//
//
//    
//    //find out which one is Human
//    //we have no idea which one is human,
//    
//    if (getHumanColor() == 'W') {
//		s.setHumanColor('W');
//        s.setComputerColor('B');
//    }
//        
//    else {
//        s.setHumanColor('B');
//        s.setComputerColor('W');
//    }
//
//	s.writeIntoFile(B);
//}

void Interface::calculateScores(Board& B) {

    //find total number of 4 in a row except for 5 in a row 
    //search every row and col values
    //if there is 4 in a row, then add 1 to the score
    cout<<"Human 4 in a row:" << B.countFour(1) << endl;
    cout<<"Computer 4 in a row:" << B.countFour(2) << endl;

    setHumanScore(B.getHumanCaptures() + B.countFour(1));
    setComputerScore(B.getComputerCaptures() + B.countFour(2));

    //the getWinner gives the 5 in a row player
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

    cout << "----Round Scores----" << endl;
    cout << "Human Score: " << getHumanScore() << endl;
    cout << "Computer Score: " << getComputerScore() << endl;
}

//int Interface::sendWinner(Board& B) {
//    //1 is human, 2 is computer
//    return B.getWinner();
//}
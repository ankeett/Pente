#include "Round.h"

//constructor
Round::Round(Player* playerList[2]) {
    this->playerList[0] = playerList[0];
	this->playerList[1] = playerList[1];
}

//Destructor
Round::~Round() {

}

/* *********************************************************************
Function Name: Round::startMenu
Purpose: Start a new round of the Pente game.
Parameters: None
Return Value: None
Algorithm:
1. Print the game board with column and row labels for the human player.
2. Start the game by calling 'startGame(B)' with the current game board 'B'.
3. Set the move count in the game board 'B' to 1 to initialize the round.
Assistance Received: None
********************************************************************* */
void Round::startMenu() {
	cout<<"----Round begins---- " << endl; 

    //Print the board with the column and row labels
    B.printBoard('W'); 
    startGame(B);

    //set the move number
    B.setMoveCount(1);

}

/* *********************************************************************
Function Name: Round::continueMenu
Purpose: Display the option to continue a Pente game.
Parameters: None
Return Value: None
Algorithm:
1. Call 'continueGame(B)' to proceed with the game continuation.
Assistance Received: None
********************************************************************* */
void Round::continueMenu() {
	cout << "----Continue the Game----" << endl;
    
	continueGame(B);
}

/* *********************************************************************
Function Name: Round::startGame
Purpose: Start and manage a Pente game with a given game board.
Parameters:
   - 'Board B': A reference to the game board used for the current game.
Return Value: None
Algorithm:
1. Display a message to prompt the player to press any key to continue, allowing them to read the initial game board.
2. Create a pointer 'currentPlayerPtr' to handle the current player's move.
3. While the game is not over:
   a. Allow the current player, pointed by 'currentPlayerPtr', to make their move on the game board.
   b. Check if the current player wants to quit the game. If yes, set 'Quit' to true, mark the game as over, and exit the game loop.
   c. Switch to the other player's turn.
   d. Increment the move count on the game board.
   e. Display the human and computer captures.
   f. Check if the game should end due to captures, and if so, determine and announce the winner.
   g. If the current player is not human, ask if they want to quit the game and set 'Quit' accordingly.
4. Calculate the scores of the game using the provided game board.
5. Print the game scores.
Assistance Received: None
********************************************************************* */
void Round::startGame(Board& B) {
    //pausing the game to give a user to chance to read the board
    cout<<"Press any key to continue" << endl;
    char c;
    cin>> c;
    cin.clear();
    cin.ignore(10000, '\n');

    cout<<"-------------------------------------------------------" << endl;

    Player* currentPlayerPtr = playerList[getCurrentPlayerIndex()];

    //while the game is not over
    while (!B.isGameOver()) {
        // Player's turn
        currentPlayerPtr->makeMove(B, B.getMoveCount());

        //check if the currentPlayer wants to quit
        if (currentPlayerPtr->getQuit() == true) {
            setQuit(true);
            B.setGameOver(true);
			return;
		}

        setCurrentPlayerIndex((currentPlayerIndex +1) %2);
        currentPlayerPtr = playerList[getCurrentPlayerIndex()];

        B.setMoveCount(B.getMoveCount() + 1);

        // Print the scores
        cout << "Human Captures: " << B.getHumanCaptures() << endl;
        cout << "Computer Captures: " << B.getComputerCaptures() << endl;


        //check captures 
        if (B.getHumanCaptures() >= 5 || B.getComputerCaptures() >= 5) {
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

/* *********************************************************************
Function Name: Round::continueGame
Purpose: Continue a Pente game using a serialized game state.
Parameters:
   - 'Board B': A reference to the game board that stores the current game state.
Return Value: None
Algorithm:
1. Create a Serialization object 's' with 'B'.
2. Read the game board from the serialized data, updating 'B' with the saved state.
3. Determine the move count based on the current state of the board.
4. Set the human color based on the serialized data.
5. If the human color is 'W' (white), set the player order as follows:
   - If the next player is "Human," set the current player index to 0 (human player).
   - If the next player is "Computer," set the current player index to 1 (computer player).
6. If the human color is 'B' (black), swap the positions of players in 'playerList' to reflect the change.
   - If the next player is "Human," set the current player index to 1 (human player).
   - If the next player is "Computer," set the current player index to 0 (computer player).
7. Set the symbols for both players.
8. Update the game board with human and computer captures.
9. Update the tournament-level human and computer scores.
10. Call 'startGame(B)' to resume the game using the loaded state.
Assistance Received: None
********************************************************************* */
void Round::continueGame(Board& B) {
    Serialization s(B);
    s.readBoard(B);
    //get the move count and set the move count
    int moveCount = B.checkEmptyBoard();
    B.setMoveCount(moveCount + 1);

    //set the human color
    setHumanColor(s.getHumanColor());

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
        //player 2 is human
        //swap the players
        //if next player is human, then set index
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

    setTournamentHumanScore(s.getHumanScore());
    setTournamentComputerScore(s.getComputerScore());

    //find the next player and set the symbol
    startGame(B);

}

/* *********************************************************************
Function Name: Round::calculateScores
Purpose: Calculate and update the scores for both human and computer players based on the current game board.
Parameters:
   - 'Board B': A reference to the game board used to determine scores.
Return Value: None
Algorithm:
1. Find the total number of "4 in a row" sequences (excluding "5 in a row") for both players by searching every row and column.
   - If a "4 in a row" sequence is found for a player, increment their score by 1.
2. Calculate and set the human score by adding the number of human captures to the count of "4 in a row" sequences for the human player.
3. Calculate and set the computer score by adding the number of computer captures to the count of "4 in a row" sequences for the computer player.
4. Check if there's a winner determined with "5 in a row" sequences on the game board:
   - If there is a winner (either human or computer), update their score by adding 5 points and set them as the winner.
Assistance Received: None
********************************************************************* */
void Round::calculateScores(Board& B) {

    //find total number of 4 in a row except for 5 in a row 
    //search every row and col values
    //if there is 4 in a row, then add 1 to the score

    int humanFour = B.countFour(1);
    int computerFour = B.countFour(2);



    setHumanScore(B.getHumanCaptures());
    setComputerScore(B.getComputerCaptures() );

    //the getWinner gives the 5 in a row player
    if (B.getWinner() != 0) {
        if (B.getWinner() == 1) {
            setWinner(1);
            setHumanScore(getHumanScore() + 5);
            humanFour--;
        }
		else {
            setWinner(2);
			setComputerScore(getComputerScore() + 5);
            computerFour--;
        }
    }
    cout<<"-------------------------------------------------------" << endl;
    cout<<"Human 4 in a row:" << humanFour<< endl;
    cout<<"Computer 4 in a row:" << computerFour << endl;
    setHumanScore(getHumanScore() + humanFour);
    setComputerScore(getComputerScore() + computerFour);

}


/* *********************************************************************
Function Name: Round::printScores
Purpose: Print the scores of the current round.
Parameters: None
Return Value: None
Algorithm:
1. Display a header to indicate the section for round scores.
2. Print the human score and computer score for the current round.
Assistance Received: None
********************************************************************* */
void Round::printScores() const{
    cout << "----Round Scores----" << endl;
    cout << "Human Score: " << getHumanScore() << endl;
    cout << "Computer Score: " << getComputerScore() << endl;
}

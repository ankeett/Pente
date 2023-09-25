#include "Tournament.h"


Tournament::Tournament()
{
	playerList[0] = new HumanPlayer('W');
	playerList[1] = new ComputerPlayer('B');
	//currentPlayerIndex = 0; //Start the game with human
}

Tournament::~Tournament()
{
	//Delete the array of player pointers
	// Delete the individual player objects
	delete playerList[0];
	delete playerList[1];

	cout << "Game Over" << endl;
}

/* *********************************************************************
Function Name: Tournament::run
Purpose: Run the Pente tournament, allowing the user to start or continue the game.
Parameters: None
Return Value: None
Algorithm:
1. Display a welcome message: "Welcome to Pente."
2. Initialize an integer variable option.
3. Create a do-while loop to repeatedly ask the user for an option.
4. Inside the loop:
   a. Prompt the user to choose an option:
	  - "Choose an option:"
	  - " 1. Start the Game"
	  - " 2. Continue the Game"
   b. Read the user's input into the 'option' variable.
   c. If the input operation is successful:
	  - If 'option' is 1, call the 'startGame()' function.
	  - If 'option' is 2, call the 'continueGame()' function.
	  - If 'option' is neither 1 nor 2, display "Invalid option. Please choose 1 or 2."
   d. If the input operation is not successful:
	  - Display "Invalid input. Please enter a valid number (1 or 2)."
	  - Clear the error state of the input stream.
	  - Ignore any remaining input on the line.
5. Continue looping as long as 'option' is not 1 or 2.
Assistance Received: None
********************************************************************* */
void Tournament::run() {
	cout << "Welcome to Pente" << endl;

	int option;

	do {
		std::cout << "Choose an option:" << std::endl;
		std::cout << " 1. Start the Game" << std::endl;
		std::cout << " 2. Continue the Game" << std::endl;

		if (std::cin >> option) {
			if (option == 1) {
				startGame();
			}
			else if (option == 2) {
				continueGame();
			}
			else {
				std::cout << "Invalid option. Please choose 1 or 2." << std::endl;
			}
		}
		else {
			std::cout << "Invalid input. Please enter a valid number (1 or 2)." << std::endl;
			// Clear the error state
			std::cin.clear();
			// Ignore any remaining input
			std::cin.ignore(1000, '\n');
		}
	} while (option != 1 && option != 2);
}


/* *********************************************************************
Function Name: Tournament::continueGame
Purpose: Continue a Pente tournament, allowing the user to resume a saved game.
Parameters: None
Return Value: None
Algorithm:
1. Initialize a boolean flag 'isFirstGame' and set it to true.
2. Enter an infinite loop to manage the tournament's flow.
3. Within the loop:
   a. Create a new game instance using the Round class with 'playerList' as parameters.
   b. If it's the first game:
	  - Display the 'continueMenu()' to allow the user to resume a saved game.
	  - Update the human and computer scores based on the saved game state.
	  - Set 'isFirstGame' to false.
	  - Set 'LastWinner' based on the human color in the saved game.
   c. If it's not the first game:
	  - Set the human color in 'game' based on 'LastWinner'.
	  - Display the 'startMenu()' to continue the tournament.
   d. Check if 'game' signals to quit the tournament:
	  - Prompt the user to decide whether to serialize the current game.
	  - If the response is 'y', serialize the game, and exit the loop.
   e. Update the human and computer scores based on the game outcome.
   f. Add 'game' to the 'games' vector.
   g. Display the current tournament scores.
   h. Prompt the user to continue playing.
   i. If 'choice' is not 'y', exit the loop.
   j. Determine the 'LastWinner' based on the tournament scores:
	  - If the human scores are higher than the computer scores, set 'LastWinner' to 1.
	  - If the human scores are lower than the computer scores, set 'LastWinner' to 2.
	  - If the scores are tied, perform a coin toss to determine 'LastWinner'.
   k. If the winner of the last game is different from 'LastWinner', swap the positions of the players.
   l. Set the symbols for the next game.
   m. Pause the game briefly to allow the user to review the scores.
4. After the loop concludes, declare the tournament winner using 'announceWinner()'.
Assistance Received: None
********************************************************************* */
void Tournament::continueGame() {
	bool isFirstGame = true;

	while (true) {	
		Round game(playerList);
		if (isFirstGame) {
			game.continueMenu();

			//set the tournament scores retreieved from file
			setHumanScores(game.getTournamentHumanScore());
			setComputerScores(game.getTournamentComputerScore());

			//1 denotes human won the last game
			isFirstGame = false;
			game.getHumanColor() == 'W' ? setLastWinner(1) : setLastWinner(2);
		}
		else {
			game.setHumanColor(getLastWinner() == 1 ? 'W' : 'B');
			game.startMenu();
		}

		if (game.quitTournament()) {
			cout << "Do you want to serialize the game? (y/n)" << endl;
			char answer;
			cin >> answer;

			answer = tolower(answer);

			if (answer == 'y') {

				//quit the game and let the tournament class serialize the game
				serializeGame(game);
			}

			break;
		}

		//add the scores
		setHumanScores(getHumanScores() + game.getHumanScore());
		setComputerScores(getComputerScores() + game.getComputerScore());

		games.push_back(game);

		// show scores of the tournament
		cout << "----Tournament Scores----" << endl;

		cout << "Your score: " << getHumanScores() << endl;
		cout << "Computer score: " << getComputerScores() << endl;

		//ask if they want to continue
		cout << "Do you want to continue? (y/n)" << endl;
		char choice;
		cin >> choice;

		choice = tolower(choice);

		if (choice != 'y') {
			break;
		}

		//determining the winner of the last game to set the White player for the next game
		if (getHumanScores() > getComputerScores()) {
			setLastWinner(1);
		}
		else if (getHumanScores() < getComputerScores()) {
			setLastWinner(2);
		}
		else {
			//toss the coin
			int toss;
			do {
				std::cout << "Toss. Choose 1 for Head and 2 for Tails: ";
				if (cin >> toss) {
					if (toss != 1 && toss != 2) {
						std::cout << "Invalid option. Please choose 1 for Head or 2 for Tails." << std::endl;
					}
				}
				else {
					std::cout << "Invalid input. Please enter a valid number (1 or 2)." << std::endl;
					// Clear the error state
					cin.clear();
					// Ignore any remaining input
					cin.ignore(1000, '\n');
				}
			} while (toss != 1 && toss != 2);

			if (toss == tossCoin()) {
				setLastWinner(1);
				cout<<"You won the toss" << endl;
				cout<<"You play White" << endl;
			}
			else {
				setLastWinner(2);
				cout << "Computer won the toss" << endl;
				cout << "You play Black" << endl;
			}


		}

		//the white player is always positioned at playerList[0]
		//swap the players if the computer won the game and the player wants to continue
		//the winner of the game will play first in the next game
		if (getLastWinner() != game.getWinner()) {
			Player* temp = playerList[0];
			playerList[0] = playerList[1];
			playerList[1] = temp;
		}
		// Set the symbols for the next game
		playerList[0]->setSymbol('W');
		playerList[1]->setSymbol('B');


		//pausing the game to give user a chance to see the scores
		cout << "Press any key to continue" << endl;
		char c;
		cin >> c;
		cin.clear();
		cin.ignore(1000, '\n');

	}


	//announce the winner
	announceWinner();
}

/* *********************************************************************
Function Name: Tournament::startGame
Purpose: Initiates a Pente game within a tournament, determining the first player through a coin toss.
Parameters: None
Return Value: None
Algorithm:
1. Perform a coin toss to decide the starting player.
2. If the user wins the toss:
   - Set the user as the starting player and display a message indicating they play as White.
   - Set 'LastWinner' to 1.
3. If the computer wins the toss:
   - Set the computer as the starting player and display a message indicating the user plays as Black.
   - Swap the positions of the players in 'playerList'.
   - Set 'LastWinner' to 2.
4. Set the symbols for the players.
5. Start the Pente game:
   a. Initialize an instance of the Round class with 'playerList'.
   b. Determine the human player's color based on 'LastWinner'.
   c. Display the game menu.
   d. If the user chooses to quit the tournament:
	  - Prompt the user if they want to serialize the game.
	  - If they confirm, serialize the game.
	  - Exit the loop.
   e. Update scores based on the game's outcome.
   f. Store the game in the 'games' vector.
   g. Display the tournament scores.
   h. Ask the user if they want to continue playing.
   i. If they choose to exit, exit the loop.
   j. If the winner of the last game is different from 'LastWinner', swap player positions.
   k. Set the symbols for the next game.
   l. Update 'LastWinner' based on scores or perform a coin toss if scores are tied.
6. Announce the winner of the tournament.
Assistance Received: None
********************************************************************* */
void Tournament::startGame() {
	int toss;

	//coin toss
	do {
		std::cout << "Toss. Choose 1 for Head and 2 for Tails: ";
		if (cin >> toss) {
			if (toss != 1 && toss != 2) {
				std::cout << "Invalid option. Please choose 1 for Head or 2 for Tails." << std::endl;
			}
		}
		else {
			std::cout << "Invalid input. Please enter a valid number (1 or 2)." << std::endl;
			// Clear the error state
			cin.clear(); 
			// Ignore any remaining input
			cin.ignore(1000, '\n'); 
		}
	} while (toss != 1 && toss != 2);

	if (toss == tossCoin()) {
		std::cout << "You won the toss" << std::endl;
		std::cout << "You play White" << std::endl;
		setLastWinner(1);
	}
	else {
		std::cout << "Computer won the toss" << std::endl;
		std::cout << "You play Black" << std::endl;

		// Swap players 
		Player* temp = playerList[0];
		playerList[0] = playerList[1];
		playerList[1] = temp;
		setLastWinner(2);
	}

	//setSymbol
	playerList[0]->setSymbol('W');
	playerList[1]->setSymbol('B');

	//start the game
	while (true) {
		Round game(playerList);

		//human is always player 1
		game.setHumanColor(getLastWinner() == 1 ? 'W' : 'B');
		game.startMenu();

		//in case, the payer wants to quit the tournament
		if (game.quitTournament()) {
			cout << "Do you want to serialize the game? (y/n)" << endl;
			char answer;
			cin >> answer;
			answer = tolower(answer);

			if (answer == 'y') {
				//quit the game and let the tournament class serialize the game
				serializeGame(game);
			}

			break;
		}

		//add the scores
		setHumanScores(getHumanScores() + game.getHumanScore());
		setComputerScores(getComputerScores() + game.getComputerScore());

		games.push_back(game);

		// show scores of the tournament
		cout << "----Tournament Scores----" << endl;

		cout << "Your score: " << getHumanScores() << endl;
		cout << "Computer score: " << getComputerScores() << endl;

		//ask if they want to continue
		cout << "Do you want to continue? (y/n)" << endl;
		char choice;
		cin >> choice;
			
		choice = tolower(choice);

		if (choice != 'y') {
			break;
		}

		//swap the players if the computer won the game and the player wants to continue
		//the winner of the game will play first in the next game
		if (getLastWinner() != game.getWinner()) {
			Player* temp = playerList[0];
			playerList[0] = playerList[1];
			playerList[1] = temp;
		}
		// Set the symbols for the next game
		playerList[0]->setSymbol('W');
		playerList[1]->setSymbol('B');

		//set the last winner
		//winner is based on the Round score
		//setLastWinner(game.getWinner());

		if (getHumanScores() > getComputerScores()) {
			setLastWinner(1);
		}
		else if (getHumanScores() < getComputerScores()) {
			setLastWinner(2);
		}
		else {
			//toss the coin
			cout<<"Toss. Choose 0 for Head and 1 for Tails" << endl;
			cin >>toss;

			if(toss == tossCoin()) {
				setLastWinner(1);
			} else {
				setLastWinner(2);
			}
		}
	}

	//announce the winner
	announceWinner();
}


/* *********************************************************************
Function Name: Tournament::announceWinner
Purpose: Announce the winner of the Pente tournament based on the scores.
Parameters: None
Return Value: None
Algorithm:
1. Check if the human player's score is greater than the computer player's score.
   - If true, display "Congratulations! You won the tournament!"
2. Check if the human player's score is less than the computer player's score.
   - If true, display "Sorry! You lost the tournament!"
3. If neither of the above conditions is met, display "It's a tie!" to indicate a tied tournament.
Assistance Received: None
********************************************************************* */
void Tournament::announceWinner() const {
	
	if(getHumanScores() > getComputerScores()) {
		cout << "Congratulations! You won the tournament!" << endl;
	} else if (getHumanScores() < getComputerScores()) {
		cout << "Sorry! You lost the tournament!" << endl;
	} else {
		cout << "It's a tie!" << endl;
	}
}

/* *********************************************************************
Function Name: Tournament::serializeGame
Purpose: Serialize and save the current state of a Pente game.
Parameters:
   - 'game' (input): A reference to the Round object representing the current game state.
Return Value: None
Algorithm:
1. Get the game board from 'game' and store it in 'B'.
2. Create a Serialization object 's' with 'B'.
3. Update 's' with the computer captures, human captures, computer score, and human score.
4. Determine the next player based on the current player's symbol:
   - If the current player's symbol matches the human color, set the next player as "Human."
   - Otherwise, set the next player as "Computer."
5. Determine the human and computer colors based on the human color stored in 'game'.
   - If 'game' indicates the human is 'W', set 's' to have human color 'W' and computer color 'B'.
   - If 'game' indicates the human is 'B', set 's' to have human color 'B' and computer color 'W'.
6. Write the game state into a file using 's'.
Assistance Received: None
********************************************************************* */
void Tournament::serializeGame(Round& game) {
	Board B = game.getBoard();
	// Save the game
	Serialization s(B);

	//set the scores and captures
	s.setComputerCaptures(B.getComputerCaptures());
	s.setHumanCaptures(B.getHumanCaptures());
	s.setComputerScore(getComputerScores());
	s.setHumanScore(getHumanScores());

	
	//get next player
	if (playerList[game.getCurrentPlayerIndex()]->getSymbol() == game.getHumanColor()) {
		s.setNextPlayer("Human");
	} else {
		s.setNextPlayer("Computer");
	}

	//set human and computer color
	if (game.getHumanColor() == 'W') {
		s.setHumanColor('W');
		s.setComputerColor('B');
	}

	else {
		s.setHumanColor('B');
		s.setComputerColor('W');
	}

	//write to file
	s.writeIntoFile(B);
}
#include "Tournament.h"

Tournament::Tournament()
{
	playerList[0] = new HumanPlayer('W');
	playerList[1] = new ComputerPlayer('B');
	currentPlayerIndex = 0; //Start the game with human
}

Tournament::~Tournament()
{
	//Delete the array of player pointers
	// Delete the individual player objects
	delete playerList[0];
	delete playerList[1];

	cout << "Game Over" << endl;
}



void Tournament::run() {
	//TODO
	//run the tournament
	//Tournament consists of 5 Rounds
	//Scores will be saved from each round
	//After 5 rounds, the winner will be announced
	//The winner will be the player with the highest score

	//Round 1
	//The first round will happen
	//then we ask users if they want a Tournament
	//If they reply yes, then we run the next round
	//If they reply no, then we announce the winner based on the win

	//the first round will begin with toss
	//the second round will begin with the player who won the first round


	//Tournament is not a 5 round game. We ask everytime to continue.
	cout << "Welcome to Pente" << endl;

	int option;

	do {
		cout << "Choose an option:" << endl;
		cout << " 1. Start the Game" << endl;
		cout << " 2. Continue the Game" << endl;
		cin >> option;
	} while (option != 1 && option != 2);

	if (option == 1) {
		startGame();
	}
	else {
		//Load the game
	}

}
	void Tournament::startGame() {

	
		int toss;
		cout<<"Toss. Choose 0 for Head and 1 for Tails" << endl;
		cin >>toss;

		if (toss == tossCoin()) {
			cout<<"You won the toss" << endl;
			cout<<"You play White" << endl;
			setLastWinner(1);
		}
		else {
			cout << "Computer won the toss" << endl;
			cout << "You play Black" << endl;
			Player* temp = playerList[0];
			playerList[0] = playerList[1];
			playerList[1] = temp;
			setLastWinner(2);
		}

		//setSymbol
		playerList[0]->setSymbol('W');
		playerList[1]->setSymbol('B');

		while (true) {
			Interface game(playerList);
			game.startMenu();

			//add the scores
			setHumanScores(getHumanScores() + game.getHumanScore());
			setComputerScores(getComputerScores() + game.getComputerScore());

			games.push_back(game);

			//ask if they want to continue
			cout << "Do you want to continue? (y/n)" << endl;
			char choice;
			cin >> choice;
			if (choice == 'n') {
				break;
			}

			//swap the players if the computer won the game and the player wants to continue
			//the winner of the game will play first in the next game
			cout<<"getLastWinner() " << getLastWinner() << endl;
			cout<<"game.getWinner() " << game.getWinner() << endl;
			if (getLastWinner() != game.getWinner()) {
				Player* temp = playerList[0];
				playerList[0] = playerList[1];
				playerList[1] = temp;
			}
			// Set the symbols for the next game
			playerList[0]->setSymbol('W');
			playerList[1]->setSymbol('B');

			//set the last winner
			setLastWinner(game.getWinner());
		}
		

		//announce the winner
		announceWinner();
	}

void Tournament::announceWinner() const {
	// show scores
	cout<<"Final Scores:" << endl;

	cout<<"Your score: " << getHumanScores() << endl;	
	cout<<"Computer score: " << getComputerScores() << endl;

	if(getHumanScores() > getComputerScores()) {
		cout << "Congratulations! You won the tournament!" << endl;
	} else if (getHumanScores() < getComputerScores()) {
		cout << "Sorry! You lost the tournament!" << endl;
	} else {
		cout << "It's a tie!" << endl;
	}
}
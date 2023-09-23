#pragma once

#include "Board.h"
#include "Player.h"
#include "Serialization.h"

class Interface {
public:
	Interface(Player * playerList[2]);
	~Interface();

	void startMenu();
	void continueMenu();
	void startGame(Board& B);
	void continueGame(Board& B);


	int getHumanScore() const {
		return humanScore;
	}

	int getComputerScore() const {
		return computerScore;
	}

	void setHumanScore(int score) {
		humanScore = score;
	}

	void setComputerScore(int score) {
		computerScore = score;
	}

	void calculateScores(Board& B);
	void printScores() const;

	int sendWinner(Board& B);

	void setWinner(int winner) {
		this->winner = winner;
	}

	int getWinner() const {
		return winner;
	}

	void serializeGame(Board& B);

	//quit the tournament or not
	bool quitTournament() const {
		return quit;
	}

	void setQuit(bool quit) {
		this->quit = quit;
	}

	void setHumanColor(char color) {
			humanColor = color;
		}

	char getHumanColor() const {
		return humanColor;
	}

	void setCurrentPlayerIndex(int index) {
			currentPlayerIndex = index;
		}

	int getCurrentPlayerIndex() const {
		return currentPlayerIndex;
	}

private:
	Board B;
	Player* playerList[2];

	//scores
	int humanScore = 0;
	int computerScore = 0;	
	
	int winner = 0;

	char humanColor = ' ';

	//quit the tournament or not
	bool quit = false;

	int currentPlayerIndex = 0;

};
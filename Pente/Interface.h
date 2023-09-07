#pragma once

#include "Board.h"
#include "Player.h"

class Interface {
public:
	Interface();
	~Interface();

	void startMenu();
	void startGame(Board B);


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



private:
	Board B;
	Player* playerList[2];
	int currentPlayerIndex;

	//scores
	int humanScore = 0;
	int computerScore = 0;
};
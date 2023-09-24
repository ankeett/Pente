#pragma once
#include "Interface.h"
#include "stdafx.h"
#include "Serialization.h"

class Tournament {
public:
	Tournament();
	~Tournament();	
	void run();

	int getHumanScores() const {
		return humanScores;
	}

	int getComputerScores() const {
		return computerScores;
	}

	void setHumanScores(int score) {
		humanScores = score;
	}
	 
	void setComputerScores(int score) {
		computerScores = score;
	}

	void announceWinner() const;

	int tossCoin()const {
		srand(time(NULL));
		int toss = rand() % 2;
		return toss;
	}

	void startGame();
	void continueGame();

	int getLastWinner() const {
		return lastWinner;
	}

	void setLastWinner(int winner) {
		lastWinner = winner;
	}

	void serializeGame(Interface& game);


	void readGame(Interface& game);

private:
	vector<Interface> games;

	Player* playerList[2];

	int humanScores = 0;
	int computerScores = 0;

	//int currentPlayerIndex;

	int lastWinner = 0;
};
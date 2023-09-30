#pragma once
#include "Round.h"
#include "stdafx.h"
#include "Serialization.h"

class Tournament {
public:
	Tournament();
	~Tournament();	
	void run();
	void serializeGame(Round& game);

	int tossCoin()const {
		srand(time(NULL));
		int toss = rand() % 2 + 1;
		return toss;
	}

	void startGame();
	void continueGame();
	void announceWinner() const;

	//getters and setters
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

	int getLastWinner() const {
		return lastWinner;
	}

	void setLastWinner(int winner) {
		lastWinner = winner;
	}

private:
	vector<Round> games;

	Player* playerList[2];

	int humanScores = 0;
	int computerScores = 0;

	int lastWinner = 0;
};
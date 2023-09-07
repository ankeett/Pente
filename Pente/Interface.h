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


	//captures
	/*int getHumanCaptures() const {
		return humanCaptures;
	}

	int getComputerCaptures() const {
		return computerCaptures;
	}

	void setHumanCaptures(int captures) {
		humanCaptures = captures;
	}

	void setComputerCaptures(int captures) {
		computerCaptures = captures;
	}*/
	void calculateScores(Board& B);
	void printScores() const;

private:
	Board B;
	Player* playerList[2];
	int currentPlayerIndex;

	//scores
	int humanScore = 0;
	int computerScore = 0;

	


};
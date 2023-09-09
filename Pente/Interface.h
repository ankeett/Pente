#pragma once

#include "Board.h"
#include "Player.h"

class Interface {
public:
	Interface(Player * playerList[2]);
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

	void calculateScores(Board& B);
	void printScores() const;

	int sendWinner(Board& B);

	void setWinner(int winner) {
		this->winner = winner;
	}

	int getWinner() const {
		return winner;
	}

private:
	Board B;
	Player* playerList[2];

	//scores
	int humanScore = 0;
	int computerScore = 0;

	
	int winner = 0;

};